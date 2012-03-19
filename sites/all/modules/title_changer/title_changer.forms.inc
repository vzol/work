<?php

/**
 * Title changer form
 * Allows to start Batch operations
 */
function title_changer_form() {
  $form = array();

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('GO'),
  );

  return $form;
}

/**
 * Submit callback for title changer form
 */
function title_changer_form_submit($form, &$form_state) {

  // Получаем массив с ID материалов
  $data = title_changer_load_nids();

  // Создаём массив с данными для батча
  $batch = array(
    'title' => t('Node processing'),
    'operations' => array(
      array('title_changer_process_node', array($data)),
    ),
    'finished' => 'title_changer_finished_callback',
    'file' => drupal_get_path('module', 'title_changer') . '/title_changer.batch.inc',
  );
  batch_set($batch);
  batch_process();
}