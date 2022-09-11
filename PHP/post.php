<?php
    date_default_timezone_set('Asia/Ho_Chi_Minh');
    $_SERVER["number"] = $_GET["number"];
    $_SERVER["updated"] = date("Y-m-d H:i:s");
    echo json_encode(array(
        'number' => $_SERVER["number"],
        'updated' => $_SERVER["updated"]
    ));
?>
