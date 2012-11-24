// Do some initial setup.
if (Drupal.jsEnabled) {
  $(document).ready(function() {
    if (typeof mpq !== 'undefined') {
      // Mixpanel library version 1.0
      mpq.push(["identify", Drupal.settings.mixpanel.defaults.uid]);
      mpq.push(["register", Drupal.settings.mixpanel.defaults]);
    }
    else {
      // Uniquely identify the user.
      mixpanel.identify(Drupal.settings.mixpanel.defaults.uid);

      // Register properties about the user.
      mixpanel.register(Drupal.settings.mixpanel.defaults);

      // Super basic support for 'People'
      mixpanel.people.identify(Drupal.settings.mixpanel.defaults.uid);
      mixpanel.people.set(Drupal.settings.mixpanel.people);
    }
  });
}
