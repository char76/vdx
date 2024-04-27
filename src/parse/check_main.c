/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
#include <stdio.h>
#include "parse.h"

extern void browse_widget( YWidget *wg );

int main( int argc, char **argv )
{
  YResult *res;
  YMethod *tmp;

  res = parse(argv[1]);
  browse_widget(res->root_widget);
  for(tmp = res->first_method; tmp; tmp = tmp->next)
    printf("void %s(Widget wg, XtPointer clientData)\n{\n%s\n}\n",
	   tmp->name, tmp->code);
  writeFile("check.out", res);

  free_YResult(res);

  res = parse("check.out");
  browse_widget(res->root_widget);
  for(tmp = res->first_method; tmp; tmp = tmp->next)
    printf("void %s(Widget wg, XtPointer clientData)\n{\n%s\n}\n",
	   tmp->name, tmp->code);

  free_YResult(res);
  return 0;
}
