<?php

/*
 * Implementation of hook_nodeapi().
 */
function mixpanel_nodeapi($node, $op) {
  if (variable_get('mixpanel_token', '') == '') {
    return;
  }
  switch($op) {
    case 'delete':
      mixpanel_track("node-deleted", array('node-title' => $node->title,
                                        'group-id' => array_pop(array_values($node->og_groups)),
                                        'node-id' => $node->nid,
                                        'node-type' => $node->type));
      break;

    case 'insert':
      mixpanel_track("node-created", array('node-title' => $node->title,
                                        'group-id' => array_pop(array_values($node->og_groups)),
                                        'node-id' => $node->nid,
                                        'node-type' => $node->type));
      break;

    case 'update':
      mixpanel_track("node-updated", array('node-title' => $node->title,
                                        'group-id' => array_pop(array_values($node->og_groups)),
                                        'node-id' => $node->nid,
                                        'node-type' => $node->type));
  }
}

/**
 * Submit function for the search form to let us track searches.
 */
function mixpanel_search_theme_form_submit($form, $form_state) {
  mixpanel_track("search", array('search-string' => $form_state['values']['search_theme_form']));
}