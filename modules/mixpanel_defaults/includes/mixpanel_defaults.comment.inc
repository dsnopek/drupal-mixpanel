<?php

/*
 * Implementation of hook_comment().
 */
function mixpanel_defaults_comment($comment, $op) {
  if (variable_get('mixpanel_token', '') == '') {
    return;
  }
  // $comment can be an object or an array.
  $comment = (object)$comment;
  $group_results = db_fetch_array(db_query("SELECT o.group_nid, n.title
                                FROM {og_ancestry} o
                                JOIN {node} n
                                ON n.nid = o.group_nid
                                WHERE o.nid = %d", $comment->nid));
  $node_results = db_fetch_array(db_query("SELECT title, type
                                    FROM {node}
                                    WHERE nid = %d", $comment->nid));
  switch($op) {
    case 'publish':
      mixpanel_track("comment-created",
        array(
         'node-id' => $comment->nid,
         'node-title' => $node_results['title'],
         'node-type' => $node_results['type'],
         'comment-id' => $comment->cid,
         'group-id' => $group_results['group_nid'],
         'group-name' => $group_results['title']
        )
      );
      break;
  }
}
