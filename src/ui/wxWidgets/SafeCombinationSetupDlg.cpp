/*
 * Copyright (c) 2003-2022 Rony Shapiro <ronys@pwsafe.org>.
 * All rights reserved. Use of the code is allowed under the
 * Artistic License 2.0 terms, as specified in the LICENSE file
 * distributed with this code, or available from
 * http://www.opensource.org/licenses/artistic-license-2.0.php
 */

/** \file SafeCombinationSetupDlg.cpp
*
*/

// Generated by DialogBlocks, Wed 21 Jan 2009 09:07:57 PM IST

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif

////@begin includes
////@end includes

#include "core/PWCharPool.h" // for CheckMasterPassword()

#include "ExternalKeyboardButton.h"
#include "SafeCombinationSetupDlg.h"
#include "wxUtilities.h"          // for ApplyPasswordFont()

#ifndef NO_YUBI
////@begin XPM images
#include "graphics/Yubikey-button.xpm"
////@end XPM images
#endif

/*!
 * SafeCombinationSetupDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( SafeCombinationSetupDlg, wxDialog )

/*!
 * SafeCombinationSetupDlg event table definition
 */

BEGIN_EVENT_TABLE( SafeCombinationSetupDlg, wxDialog )

////@begin SafeCombinationSetupDlg event table entries
#ifndef NO_YUBI
  EVT_BUTTON( ID_YUBIBTN, SafeCombinationSetupDlg::OnYubibtnClick )

EVT_TIMER(POLLING_TIMER_ID, SafeCombinationSetupDlg::OnPollingTimer)
#endif

  EVT_BUTTON( wxID_OK, SafeCombinationSetupDlg::OnOkClick )

  EVT_BUTTON( wxID_CANCEL, SafeCombinationSetupDlg::OnCancelClick )

////@end SafeCombinationSetupDlg event table entries
END_EVENT_TABLE()

/*!
 * SafeCombinationSetupDlg constructors
 */
SafeCombinationSetupDlg::SafeCombinationSetupDlg(wxWindow *parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
  wxASSERT(!parent || parent->IsTopLevel());
////@begin SafeCombinationSetupDlg creation
  SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
  wxDialog::Create( parent, id, caption, pos, size, style );

  CreateControls();
  if (GetSizer())
  {
    GetSizer()->SetSizeHints(this);
  }
  Centre();
////@end SafeCombinationSetupDlg creation
#ifndef NO_YUBI
  SetupMixin(FindWindow(ID_YUBIBTN), FindWindow(ID_YUBISTATUS));
  m_pollingTimer = new wxTimer(this, POLLING_TIMER_ID);
  m_pollingTimer->Start(YubiMixin::POLLING_INTERVAL);
#endif
}

SafeCombinationSetupDlg* SafeCombinationSetupDlg::Create(wxWindow *parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
  return new SafeCombinationSetupDlg(parent, id, caption, pos, size, style);
}

/*!
 * SafeCombinationSetupDlg destructor
 */

SafeCombinationSetupDlg::~SafeCombinationSetupDlg()
{
////@begin SafeCombinationSetupDlg destruction
////@end SafeCombinationSetupDlg destruction
#ifndef NO_YUBI
  delete m_pollingTimer;
#endif
}

/*!
 * Control creation for SafeCombinationSetupDlg
 */

void SafeCombinationSetupDlg::CreateControls()
{
////@begin SafeCombinationSetupDlg content construction
  SafeCombinationSetupDlg* itemDialog1 = this;

  wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
  itemDialog1->SetSizer(itemBoxSizer2);

  wxStaticText* itemStaticText3 = new wxStaticText( itemDialog1, wxID_STATIC, _("A new password database will be created.\nThe safe combination will be used to encrypt the password database file.\nYou can use any keyboard character. The combination is case-sensitive."), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer2->Add(itemStaticText3, 0, wxALIGN_LEFT|wxALL, 15);

  wxFlexGridSizer* itemGridSizer4 = new wxFlexGridSizer(2, 0, 10);
  itemBoxSizer2->Add(itemGridSizer4, 0, wxLEFT|wxRIGHT|wxEXPAND, 15);

  wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _("Safe Combination:"), wxDefaultPosition, wxDefaultSize, 0 );
  itemGridSizer4->Add(itemStaticText5, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxTextCtrl* itemTextCtrl6 = new wxTextCtrl( itemDialog1, ID_PASSWORD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
  itemGridSizer4->Add(itemTextCtrl6, 0, wxALIGN_LEFT|wxALL|wxEXPAND, 5);

  wxStaticText* itemStaticText7 = new wxStaticText( itemDialog1, wxID_STATIC, _("Verify:"), wxDefaultPosition, wxDefaultSize, 0 );
  itemGridSizer4->Add(itemStaticText7, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxTextCtrl* itemTextCtrl8 = new wxTextCtrl( itemDialog1, ID_VERIFY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
  itemGridSizer4->Add(itemTextCtrl8, 0, wxALIGN_LEFT|wxALL|wxEXPAND, 5);

#ifndef NO_YUBI
  m_YubiBtn = new wxBitmapButton( itemDialog1, ID_YUBIBTN, itemDialog1->GetBitmapResource(wxT("graphics/Yubikey-button.xpm")), wxDefaultPosition, itemDialog1->ConvertDialogToPixels(wxSize(40, 15)), wxBU_AUTODRAW );
  itemGridSizer4->Add(m_YubiBtn, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM|wxSHAPED, 5);

  m_yubiStatusCtrl = new wxStaticText( itemDialog1, ID_YUBISTATUS, _("Please insert your YubiKey"), wxDefaultPosition, wxDefaultSize, 0 );
  itemGridSizer4->Add(m_yubiStatusCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
#endif

  itemGridSizer4->AddGrowableCol(1, 2);
  
  wxStdDialogButtonSizer* itemStdDialogButtonSizer11 = new wxStdDialogButtonSizer;

  itemBoxSizer2->Add(itemStdDialogButtonSizer11, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 10);
  wxButton* itemButton12 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStdDialogButtonSizer11->AddButton(itemButton12);

  wxButton* itemButton13 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStdDialogButtonSizer11->AddButton(itemButton13);

  wxButton* itemButton14 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStdDialogButtonSizer11->AddButton(itemButton14);

  itemStdDialogButtonSizer11->Realize();

  // Set validators
  itemTextCtrl6->SetValidator( wxGenericValidator(& m_password) );
  itemTextCtrl8->SetValidator( wxGenericValidator(& m_verify) );
////@end SafeCombinationSetupDlg content construction
}

/*!
 * Should we show tooltips?
 */

bool SafeCombinationSetupDlg::ShowToolTips()
{
  return true;
}

/*!
 * Get bitmap resources
 */

#ifndef NO_YUBI
wxBitmap SafeCombinationSetupDlg::GetBitmapResource( const wxString& name )
{
  // Bitmap retrieval
////@begin SafeCombinationSetupDlg bitmap retrieval
  if (name == _T("graphics/Yubikey-button.xpm"))
  {
    wxBitmap bitmap(Yubikey_button_xpm);
    return bitmap;
  }
  return wxNullBitmap;
////@end SafeCombinationSetupDlg bitmap retrieval
}
#endif

/*!
 * Get icon resources
 */

wxIcon SafeCombinationSetupDlg::GetIconResource( const wxString& WXUNUSED(name) )
{
  // Icon retrieval
////@begin SafeCombinationSetupDlg icon retrieval
  return wxNullIcon;
////@end SafeCombinationSetupDlg icon retrieval
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void SafeCombinationSetupDlg::OnOkClick(wxCommandEvent& WXUNUSED(evt))
{
  if (Validate() && TransferDataFromWindow()) {
    if (m_password != m_verify) {
      wxMessageDialog err(this, _("The two entries do not match."),
                          _("Error"), wxOK | wxICON_EXCLAMATION);
      err.ShowModal();
      return;
    }
    if (m_password.empty()) {
      wxMessageDialog err(this, _("Please enter the key and verify it."),
                          _("Error"), wxOK | wxICON_EXCLAMATION);
      err.ShowModal();
      return;
    }
    // Vox populi vox dei - folks want the ability to use a weak
    // passphrase, best we can do is warn them...
    // If someone want to build a version that insists on proper
    // passphrases, then just define the preprocessor macro
    // PWS_FORCE_STRONG_PASSPHRASE in the build properties/Makefile
    // (also used in CPasskeyChangeDlg)
#ifndef _DEBUG // for debug, we want no checks at all, to save time
    StringX errmess;
    if (!CPasswordCharPool::CheckMasterPassword(tostringx(m_password), errmess)) {
      wxString cs_msg;
      cs_msg = _("Weak passphrase:");
      cs_msg += wxT("\n\n");
      cs_msg += errmess.c_str();
#ifndef PWS_FORCE_STRONG_PASSPHRASE
      cs_msg += wxT("\n");
      cs_msg += _("Use it anyway?");
      wxMessageDialog mb(this, cs_msg, _("Warning"),
                      wxYES_NO | wxNO_DEFAULT | wxICON_HAND);
      int rc = mb.ShowModal();
    if (rc == wxID_NO)
      return;
#else
    cs_msg += wxT("\n");
    cs_msg += _("Please try another");
    wxMessageDialog mb(this, cs_msg, _("Error"), wxOK | wxICON_HAND);
    mb.ShowModal();
    return;
#endif // PWS_FORCE_STRONG_PASSPHRASE
    }
#endif // _DEBUG
    EndModal(wxID_OK);
  }
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
 */

void SafeCombinationSetupDlg::OnCancelClick( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in SafeCombinationSetupDlg.
  // Before editing this code, remove the block markers.
  event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in SafeCombinationSetupDlg.
}

#ifndef NO_YUBI
void SafeCombinationSetupDlg::OnPollingTimer(wxTimerEvent &evt)
{
  if (evt.GetId() == POLLING_TIMER_ID) {
    HandlePollingTimer(); // in YubiMixin
  }
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_YUBIBTN
 */

void SafeCombinationSetupDlg::OnYubibtnClick(wxCommandEvent& WXUNUSED(event))
{
  if (Validate() && TransferDataFromWindow()) {
    if (m_password != m_verify) {
      wxMessageDialog err(this, _("The two entries do not match."),
                          _("Error"), wxOK | wxICON_EXCLAMATION);
      err.ShowModal();
      return;
    }
    StringX response;
    bool oldYubiChallenge = ::wxGetKeyState(WXK_SHIFT); // for pre-0.94 databases
    if (PerformChallengeResponse(this, tostringx(m_password), response, oldYubiChallenge)) {
      m_password = response.c_str();
      EndModal(wxID_OK);
    }
  }
}
#endif
