<?php

/**
 * Process every item in batch
 */
function title_changer_process_node($nodes, &$context) {

  // Количество материалов, которые будут обработаны одной пачкой за раз
  $limit = 1;

  // Задаём начальные значения для батча
  if (empty($context['sandbox']['progress'])) {
    // Текущее количество обработанных материалов
    $context['sandbox']['progress'] = 0;
    // Общее количество материалов, которые надо обработать
    $context['sandbox']['max'] = count($nodes);
  }

  // Сохраняем массив с материалами в переменную батча
  if(empty($context['sandbox']['items'])) {
    $context['sandbox']['items'] = $nodes;
  }

  $counter = 0;
  if(!empty($context['sandbox']['items'])) {

    // Убираем из массива с данными уже обработанные материалы
    if ($context['sandbox']['progress'] != 0) {
      array_splice($context['sandbox']['items'], 0, $limit);
    }

    foreach ($context['sandbox']['items'] as $nid) {
      if ($counter != $limit) {
        
        // Загружаем материал
        $node = node_load($nid);
        // Загружаем автора материала
        $user = user_load($node->uid);
        // Добавляем к заголовку материала автора, который его создал
        //
       // str_replace("%body%", "black", "<body text='%body%'>");
        $node->title .= t(' Created by !user', array('!user' => $user->name));
        // Сохраняем материал
        node_save($node);

        // Увеличиваем счётчики
        $counter++;
        $context['sandbox']['progress']++;

        $context['message'] = t('Now processing node %progress of %count', array('%progress' => $context['sandbox']['progress'], '%count' => $context['sandbox']['max']));
        $context['results']['processed'] = $context['sandbox']['progress'];
      }
    }
  }

  // Проверка, не пора ли закончить обработку данных.
  // Как только количество обработанных будет равно общему количеству материалов - обработка завершится
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
      $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finish callback for Batch
 */
function title_changer_finished_callback($success, $results, $operations) {
  if ($success) {
    $message = format_plural($results['processed'], 'One node processed.', '@count nodes processed.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
}