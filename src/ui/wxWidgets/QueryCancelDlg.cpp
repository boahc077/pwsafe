/*
 * Copyright (c) 2003-2021 Rony Shapiro <ronys@pwsafe.org>.
 * All rights reserved. Use of the code is allowed under the
 * Artistic License 2.0 terms, as specified in the LICENSE file
 * distributed with this code, or available from
 * http://www.opensource.org/licenses/artistic-license-2.0.php
 */

/** \file pwFiltersBoolDlg.cpp
*
*/

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "QueryCancelDlg.h"
#include "wxUtilities.h"

void QueryCancelDlg::OnClose(wxCloseEvent &event) {
  if (event.CanVeto()) {
    // when trying to closing app/db, don't ask questions when data changed
    if (!SyncAndQueryCancel(!IsCloseInProgress())) {
      event.Veto();
      return;
    }
  }
  EndDialog(wxID_CANCEL); // cancel directly (if we skip event, OnCancel will be called and ask one more time)
}

void QueryCancelDlg::OnCancelClick(wxCommandEvent& /*event*/) {
  if (SyncAndQueryCancel(true)) {
    EndModal(wxID_CANCEL);
  }
}

/**
 * Check if something changes and ask to discard changes
 @return true, if cancel allowed
*/
bool QueryCancelDlg::SyncAndQueryCancel(bool showDialog) {
  if (!(Validate() && TransferDataFromWindow()) || IsChanged()) {
    if (showDialog) {
      auto res = wxMessageDialog(
        nullptr,
        _("Unsaved changes have been made. Are you sure you wish to cancel?"), wxEmptyString,
        wxYES_NO | wxNO_DEFAULT | wxICON_EXCLAMATION
      ).ShowModal();
      if (res == wxID_YES) {
        return true;
      }
    }
    return false;
  }
  return true;
}

