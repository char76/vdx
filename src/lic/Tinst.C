/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Tinst.C,v $
 *  $Date: 1999/08/27 15:32:04 $
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
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:04  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.5  1998/02/10  00:47:42  lazy
 * Add ref for WIdClassPopupCallback
 *
 * Revision 1.4  1997/12/14  19:08:51  lazy
 * remove template instance for EnumType
 *
 * Revision 1.3  1997/09/13  16:02:04  lazy
 * WidClassCategory added.
 *
 * Revision 1.2  1997/09/02  22:23:50  lazy
 * GlobalResTextView.
 *
 * Revision 1.1  1997/07/25  20:31:18  lazy
 * Initial revision
 *
 */

//
// Template instantiation file
//

#include "Lproject.h"
#include "Lwidget.h"
#include "Lcreator.h"
#include "Lresource.h"
#include "InterfaceInfo.h"
#include "Lpalette.h"
#include "LresEditor.h"
#include "FontSelect.h"
#include "ColorSelect.h"
#include "MenuEdit.h"
#include "TextEdit.h"
#include "MainWindow.h"
#include "Ltmpl.h"
#include "WidgetPalette.h"
#include "TemplateView.h"
#include "WidBrowseView.h"
#include "WidResEditor.h"
#include "ProjectSettings.h"
#include "AttachmentEditor.h"
#include "GlobalResEditor.h"
#include "TransformDialog.h"

#include <lac/IconView.h>

#include <lac/Ref.C>
#include <lac/RefArray.C>
#include <lac/ConModel.C>
#include <lac/TreeNode.C>

template class TreeNode<Lwidget>;
template class Container<Linterface>;
template class RefArray<Lresource>;
template class Ref<Linterface>;
template class RefArray<Linterface>;
template class Ref<WidgetView>;
template class Ref<Lwidget>;
template class Container<Lcreator>;
template class RefArray<MethodInfo>;
template class RefArray<RelationInfo>;
template class RefArray<CallbackInfo>;
template class RefArray<HeaderInfo>;
template class RefArray<WidgetInfo>;
template class RefArray<ResView>;
template class Ref<IconView>;
template class Ref<FontSelect>;
template class Ref<ValueView>;
template class Ref<WidNameView>;
template class Ref<ColorSelect>;
template class Ref<InterfaceView>;
template class RefArray<Lwidget>;
template class RefArray<LresRelation>;
template class Ref<LresRelation>;
template class Ref<Lresource>;
template class RefArray<WidgetView>;
template class Ref<WidgetController>;
template class TSortArray<Lresource>;
template class TArray<Lresource>;
template class Ref<LresEditor>;
template class RefArray<LresEditor>;
template class Ref<ResView>;
template class RefArray<LinkInfo>;
template class Ref<LinkInfo>;
template class Ref<ResourceFileInfo>;
template class Ref<WidgetInfo>;
template class Ref<HeaderInfo>;
template class Ref<CallbackInfo>;
template class Ref<MethodInfo>;
template class Ref<RelationInfo>;
template class RefArray<LangInfo>;
template class Ref<LangInfo>;
template class RefArray<Lcreator>;
template class Ref<Lcreator>;
template class TArray<char>;
template class Ref<ResourceInfo>;
template class RefArray<ResourceInfo>;
template class Ref<WidgetBrowse>;
template class RefArray<WidgetBrowse>;
template class Ref<MenuEdit>;
template class RefArray<MenuEdit>;
template class Ref<TextEdit>;
template class RefArray<TextEdit>;
template class Ref<MainWindow>;
template class RefArray<MainWindow>;
template class Ref<LocalHeaderInfo>;
template class RefArray<LocalHeaderInfo>;
template class Ref<Lfile>;
template class RefArray<Lfile>;
template class Ref<WidgetPalette>;
template class Ref<TreeView>;
template class Ref<Lpalette>;
template class RefArray<Lpalette>;
template class Container<Lpalette>;
template class Container<Lwidget>;
template class Ref<TemplateView>;
template class RefArray<TemplateView>;
template class Ref<WidgetTreeView>;
template class Ref<WidBrowseView>;
template class RefArray<WidBrowseView>;
template class Ref<WidResEditor>;
template class RefArray<WidResEditor>;
template class Ref<WidgetIconView>;
template class Ref<ProjectSettings>;
template class RefArray<ProjectSettings>;

template class Ref<WidManageView>;
template class Ref<WidDescriptionView>;
template class Ref<WidQuickHelpView>;
template class Ref<WidHelpNodeView>;
template class RefArray<WidHelpNodeView>;

template class Ref<LcreatorIconView>;

template class Ref<AttachmentEditor>;
template class RefArray<AttachmentEditor>;
template class Ref<AttachmentEditor::AttachData>;
template class RefArray<AttachmentEditor::AttachData>;

template class Ref<GlobalResEditor>;
template class RefArray<GlobalResEditor>;
template class Ref<GlobalResEditor::GlobalResTextView>;

template class Ref<TransformDialog>;
template class RefArray<TransformDialog>;

template class Ref<Lproject>;

template class Ref<WidClassCategory>;
template class RefArray<WidClassCategory>;
template class Container<WidClassCategory>;

template class Ref<WidCategoryMenu>;
template class RefArray<WidCategoryMenu>;

template class Ref<WidClassButton>;
template class RefArray<WidClassButton>;

template class Ref<WidClassCallback>;
template class Ref<WidClassPopupCallback>;

