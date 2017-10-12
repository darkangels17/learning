<?php
class UsersController extends AppController {
	var $name = "Users";
	/*var $helpers = array("Html");
   	var $component = array("Session");*/
	function login() {
		 $err = "";
		 
		 $icsString = "SADASDASDASD";
		 $response = $this->response;
		 $response->body($icsString);
		 
		 $response = $response->withType('ics');
		 
		 // Optionally force file download
		 $response = $response->withDownload('filen.ics');
		 
		 // Return response object to prevent controller from trying to render
		 // a view.
		 return $response;
		 
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