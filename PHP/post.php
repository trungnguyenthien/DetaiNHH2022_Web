<?php
    date_default_timezone_set('Asia/Ho_Chi_Minh');
    $_SESSION["number"] = $_GET["number"];
    $_SESSION["updated"] = date("Y-m-d H:i:s");
    echo json_encode(array(
        'number' => $_SESSION["number"], 
        'updated' => $_SESSION["updated"]
    ));
?>