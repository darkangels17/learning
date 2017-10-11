<?php
class UsersController extends AppController {
	var $name = "Users";
	/*var $helpers = array("Html");
   	var $component = array("Session");*/
	function login() {
		 $err = "";
		//print_r($this->data);
		$this->User->set($this->data);
		$user = $this->data;
		print_r($this->data);
		if($user){
			if(!$this->User->validate1()) {
				$this->Session->write("session",$user['User']['email']);
			}
		}
	}

	function index(){

	}
}
?>