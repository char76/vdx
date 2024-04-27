/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Tinst.C,v $
 *  $Date: 1999/08/27 15:30:18 $
 *  $Revision: 1.1.1.1.2.1 $
 *
 *  Copyright 1995, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: Tinst.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:18  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  19:49:54  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:12:54  lazy
 * Initial revision
 *
 */

// --------------------------------------
// template instances
// ---------------------------------------

#include "Ref.C"
#include "RefArray.C"
#include "ConModel.C"
#include "TreeNode.C"

#include "Model.h"
#include "View.h"
#include "SensitiveView.h"
#include "IconView.h"
#include "TreeView.h"
#include "LicView.h"
#include "Controller.h"
#include "HelpNode.h"
#include "MLXHelp.h"
#include "OptionMenuView.h"
#include "CallbackMethod.h"

template class Ref<Model>;
template class Ref<TreeNodeView>;
template class Ref<Icon>;
template class Ref<TreeNodeView::ExpandIcon>;
template class Ref<TextRecView>;
template class Ref<PixmapRecView>;
template class Ref<StatePixmapRecView>;
template class Ref<Selectable>;
template class Ref<View>;
template class Ref<SensitiveRec>;
template class Ref<WinView>;
template class Ref<LicView>;
//template class Ref<TreeNodeView>;
template class RefArray<Selectable>;
template class RefArray<SensitiveRec>;
template class RefArray<LicView>;
template class RefArray<WinView::CBInfo>;
template class TreeNode<HelpNode>;
template class Ref<HelpNode>;
template class RefArray<HelpNode>;
template class Ref<MLXHelp>;
template class RefArray<View>;
template class TArray<Model::ViewData>;
template class TArray<_QuickHelpData>;
template class RefArray<TreeNodeView>;
template class Ref<WinView::CBInfo>;
template class TArray<WinView::IconData>;
template class Ref<StatePixmapRecView::StatePixmap>;
template class RefArray<StatePixmapRecView::StatePixmap>;
template class Ref<Iconable>;
template class RefArray<Iconable>;
template class Ref<MenuEntry>;
template class RefArray<MenuEntry>;
template class Ref<Controller>;
template class RefArray<Controller>;
template class Ref<HelpNodeLink>;
template class RefArray<HelpNodeLink>;
template class Ref<ContainerBase>;
template class Ref<LabelView>;
template class RefArray<LabelView>;
template class Ref<MenuEntryWidget>;
template class RefArray<MenuEntryWidget>;
template class Ref<CallbackMethod>;
template class RefArray<CallbackMethod>;


