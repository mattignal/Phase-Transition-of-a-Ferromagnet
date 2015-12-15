#include <stdio.h>

#include "progressbar.h"

void text_progress_bar (int step, int max, int barwidth, char *message, FILE * fp)
{
    int report = max / barwidth;
    fprintf (fp, "\r");
    fprintf (fp, " %16s: ", message);
    fprintf (fp, " %8d steps:", max);
    fprintf (fp, " %3d%% [", (int) (100. * step / max));
    for (int k = 1; k <= step / report; k++)
    {
        fprintf (fp, "=");
    }
    for (int k = step / report + 1; k < max / report; k++)
    {
        fprintf (fp, " ");
    }
    fprintf (fp, "]");
    fflush (fp);
}
