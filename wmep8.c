/* wmep8.c - Clock that countdowns to Star Wars Episode VIII
 *
 *  Copyright (c) 2016 Andrew Lind
 *  Copyright (c) 1999 Hadess
 *  Copyright (c) 1999 Bishop
 *  Copytight (c) 1997, 1998 Martijn Pieterse and Antoine Nulle
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, 
 *  USA.
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <X11/X.h>
#include <X11/xpm.h>
#include "xutils.h"
#include "wmep8-master.xpm"
#include "wmep8-master-mask.xbm"
#include "wmep8-numbers.xpm"

char    TimeColor[30]           = "#ffff00";
char    BackgroundColor[30]     = "#181818";

Pixmap pixnum, masknum;

void DrawDate(int dtg) {

   char temp[16];
   char *p = temp;
   int i,k;

   sprintf(temp, "%3d", dtg);
   k = 43;
   for (i=0; i<3; i++) {
      copyXPMAreaWithPixmap(pixnum, (*p-'0')*5, 0, 5, 11, k, 46);
      k += 5;
      p++;
   }
}


int
main(int argc, char **argv)
{
    unsigned height, width;
    long starttime;
    long curtime;
    long targettime;
    long difftime;
    int dayss;

    starttime = time(0);

    initXwindow(argc, argv);
    openXwindow(argc, argv, wmep8_master_xpm, wmep8_master_mask_bits, wmep8_master_mask_width, wmep8_master_mask_height);
    MakePixmapFromData(wmep8_numbers_xpm, &pixnum, &masknum, &height, &width);
    
    while (1) {
	XEvent ev;
	
	curtime = time(0);
	targettime = 1513249200;
	difftime = targettime - curtime;
	dayss=difftime/86400;
	
	if (curtime >= starttime) {
	   DrawDate(dayss);
	}

	
	/* handle all pending X events */
	while (XPending(display)) {
	    XNextEvent(display, &ev);
	    switch(ev.type){
                case Expose:
                        RedrawWindow();
                        break;
            }

	}
	
	/* Sleep 0.3 seconds */
	usleep(300000L);
    }

    return 0;
}


Bool
MakePixmapFromData(char **data, Pixmap *pixmap, Pixmap *mask,
                     unsigned *width, unsigned *height)
{
    XpmAttributes xpmat;

    xpmat.valuemask = XpmCloseness;
    xpmat.closeness = 40000;

    if (XpmCreatePixmapFromData(display, iconwin, data, pixmap, mask,
                                &xpmat)!=0) {
        return False;
    }

    *width = xpmat.width;
    *height = xpmat.height;

    return True;
}
