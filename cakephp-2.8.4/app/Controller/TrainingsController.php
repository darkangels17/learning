<?php
class TrainingsController extends AppController {
	var $name = "Trainings";
	var $component = array("Session");
	function login() {
		 $err = "";
		$this->Training->set($this->data);
		$training = $this->data;
		if($training){
			if($this->Training->validateLogin()== TRUE) {
				$this->Session->write("session",$training['Trainings']['Email']);
				$this->redirect('index');
			} 
		}
	}
	
	function index(){
	   $arrayUser = $this->Training->getListUser();
	   print_r($arrayUser);
	   $this->set('listUser', $arrayUser);
	}
}
?>