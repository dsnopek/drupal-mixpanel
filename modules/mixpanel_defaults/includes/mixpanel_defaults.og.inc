<?php

/*
 * Implementation of hook_og().
 */
function mixpanel_defaults_og($op, $gid, $uid, $args) {
  if (variable_get('mixpanel_token', '') == '') {
    return;
  }
  $account = user_load($uid);
  $group_node = node_load($gid);
  switch ($op) {
    case 'user insert':
      mixpanel_track("group-join", array("group-id" => $gid, "group-name" => $group_node->title), $account);
      break;

    case 'user delete':
      mixpanel_track("group-left", array("group-id" => $gid, "group-name" => $group_node->title), $account);
      break;
  }
}
