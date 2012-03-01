<?php 

/**
 * If you wish to do metric logging from your backend, the best method of doing this is
 * to do it in a non-blocking way. This will let your pages continue to execute at
 * about the same speed  while logging metric data in the background. Please note: If
 * you're on a shared host, you may be limited in logging metric data with a background
 * process.
 *
 * Feel free to modify this code to your own environments liking.
 *
 */
class MetricsTracker {
    public $token;
    public $host = 'http://api.mixpanel.com/';
    public function __construct($token_string) {
        $this->token = $token_string;
    }
    function track($event, $properties=array()) {
        $params = array(
            'event' => $event,
            'properties' => $properties
            );

        if (!isset($params['properties']['token'])){
            $params['properties']['token'] = $this->token;
        }
        $url = $this->host . 'track/?data=' . base64_encode(json_encode($params));
        // You still need to run as a background process.
        exec("curl '" . $url . "' >/dev/null 2>&1 &");
        // Uncomment the following line and comment the previous line to send events to /tmp/drupal_debug (devel module must be installed).
        //dd($params);
    }

    function track_funnel($funnel, $step, $goal, $properties=array()) {
        $properties['funnel'] = $funnel;
        $properties['step'] = $step;
        $properties['goal'] = $goal;
        $this->track('mp_funnel', $properties);
    }
}
