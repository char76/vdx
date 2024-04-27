/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ----------------------------
// FontSelect.h
// Do not edit
// ----------------------------

#ifndef _FontSelect_H_
#define _FontSelect_H_

#include "FontSelect_base.h"

#include "LresEditor.h"
#include <lac/TArray.h>

class FontSelect : public FontSelect_base {
private:
  Ref<ValueView> textResView;

  static char **fonts;                // Nur einmal von X-Server holen
  static unsigned int count;

  TArray<char> showedFonts;           // Fonts in der Liste

  void delNotify( BaseRef *toDel );
  void setFont(char *t);

  void readFonts(char *pattern);
  void updateOptionMenus();
  void queryFromFonts(TArray<char> &c,TArray<char> &f,TArray<char> &s);

  Boolean matchPattern(char *font, char *pattern);

protected:
  virtual void fontSelectOk(Widget,XtPointer);
  virtual void fontSelectCancel(Widget,XtPointer);
  virtual void fontSelectHelp(Widget,XtPointer);
  virtual void fontTextChanged(Widget,XtPointer);
  virtual void fontSelected(Widget,XtPointer);
  virtual void companyChanged(Widget,XtPointer);
  virtual void familyChanged(Widget,XtPointer);
  virtual void sizeChanged(Widget,XtPointer);

public:
  FontSelect(ValueView *t);
  FontSelect(Widget parent = NULL, ArgList args = NULL, Cardinal n = 0);

  ~FontSelect();
};


FontSelect *createFontSelect(Widget parent, ArgList args, Cardinal n);

#endif /* Don't add stuff after this #endif */
