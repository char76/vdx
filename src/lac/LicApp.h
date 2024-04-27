/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
#ifndef _LICAPP_H_
#define _LICAPP_H_

#include <lac/LicView.h>
#include <lac/MsgCat.h>
#include <lac/Ref.h>
#include <lac/Lobject.h>

class LicApp : public Lobject {
protected:
  Ref<LicView> mainWindow;
  Ref<MsgCat>  msgCat;

public:
  LicApp(Cardinal argc, char **argv);
  ~LicApp();

  MsgCat *getMsgCat() { return msgCat; }
  
};

#endif /* Don't add stuff after this endif */
