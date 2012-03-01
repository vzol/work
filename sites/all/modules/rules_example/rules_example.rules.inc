<?php 
/**
 * @file
 * Rules example actions, conditions, events
 * rules_example.rules.inc
 */

/**
 * Implements hook_rules_action_info()
 *
 */

 function rules_example_rules_action_info(){
  
   $actions = array(
    'rules_example_action_hello_world' => array(
       'label' => t('Print hello world on page'),
       'group' => t('Rules examples'),
     ),    
     'rules_example_action_hello_user' => array(
        'label' => 'Say hello to are selected user',
        'group' => t('Rules examples'),
        'parameter' => array(
           'account' => array(
            'type' => 'user',
            'label' => t('User to say hello to '),
            ),
        ),
     ),
    );
  if (module_exists('views')) {
    $actions['rule_example_action_get_view_results'] = array(
    'label' => t('Get the number of results in a view'),
    'group' => t('Rules examples'),
    'parameter' => array(
       'view_name' => array(
        'type' => 'text',
        'label' => t('The view to use to load the number of result'),
        'options list' => 'rules_example_views_list',
        ), 
    ),
    );
  }
  
  return $actions;  
 }
 /**
  *the action function for rules_example_action_hello_world
  *
  */
 function rules_example_action_hello_world(){
    drupal_set_message(t('Hello world'));
 }
 
 /*
  *The actions functions for the rules_example_action_hello_user
  *
  *The account parameter is the user object 
  */ 
 
 function rules_example_action_hello_user($account){
    drupal_set_message(t('Hello @username',
        array('@username' => $account->name)));
 }
 
/*
 *
 *
 */  
 function rule_example_action_get_view_results($view_name) {
    dpm($view_name);
 }
 
 /*
  *
  *
  */
 function rules_example_views_list() {
   foreach( views_get_all_views() as $view_name => $view_object );
 }
 
 ?>