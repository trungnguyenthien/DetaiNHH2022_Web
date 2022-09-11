<?php
    date_default_timezone_set('Asia/Ho_Chi_Minh');

    $updated = date("Y-m-d H:i:s", $_SESSION["updated"]);
    $checked = date("Y-m-d H:i:s", strtotime('+2 minutes', $now));

    if($updated < $checked) {
        echo json_encode(array(
            'number' => $_SESSION["number"],
            'updated' => $_SESSION["updated"]
        ));
    } else {
        echo json_encode(array(
            'number' => null,
            'updated' => null
        ));
    }
?>
