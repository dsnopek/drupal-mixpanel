<?php

/*
 * Implementation of hook_user().
 */
function mixpanel_defaults_user($op, $edit, $account, $category) {
  if (variable_get('mixpanel_token', '') == '') {
    return;
  }
  switch($op) {
    case 'insert':
      mixpanel_track("user-inserted", null, $account);
      break;

    case 'delete':
      mixpanel_track("user-deleted", null, $acccount);
      break;

    case 'update':
      // We can't use this unfortunately as the LDAP module updates a person's account each time they login.
      // We'll use hook_form_alter instead to detect someone submittng an account update.
      //mixpanel_track("user-account-updated", null, $account);
      break;

    case 'login':
      mixpanel_track("user-login", null, $account);
      break;

    case 'logout':
      mixpanel_track("user-logout", null, $account);
      break;
  }
}

/**
 * Submit function for contact_mail_user to track usage of the contact form.
 */
function mixpanel_defaults_contact_mail_user_submit($form, $form_state) {
  mixpanel_track("contact-form-user");
}

/**
 * Submit function for the user_profile_form to let us track user changes
 * to their accounts.
 */
function mixpanel_defaults_user_profile_form_submit($form, $form_state) {
  mixpanel_track("user-account-updated");

  // If a picture was uploaded, submit an event for that as well.
  if (isset($form_state['values']['picture'])) {
    mixpanel_track("user-picture-changed");
  }
}
