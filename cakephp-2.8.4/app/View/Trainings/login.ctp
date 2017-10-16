 <label><a href = "#">管理システム</a></label>
<?php
 echo $this->Form->create('Training');
	$error = $this->Form->isFieldError('checkExist') ? $this->Form->error('checkExist') : '';  
 if(!$this->Form->isFieldError('email') && !$this->Form->isFieldError('password')&& isset($error)){
 	echo $this->Form->label('InforError',"$error") ;
 }
 ?>
 <?php	
 echo $this->Form->hidden('checkExist');			
 echo $this->Form->input('email',['label'=>'Mail address']);
 echo $this->Form->input('password',['label'=>'Password']);
 echo $this->Form->end('Login');
?>
