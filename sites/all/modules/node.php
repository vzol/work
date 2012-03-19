<?php
/**
* Implements of hook_menu_alter().
*/
function internetdevels_menu_alter(&$callbacks) {
unset($callbacks['node']);
}