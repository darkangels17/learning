<?php
class User extends AppModel{
	  function validate1(){
	    $this->validate = array(
            'password' => array(
                'not empty' => array(
                    'rule' => 'notBlank',
                    'message' => 'Mật khẩu không được để trống'
                )
            ),
            'email' => array(
                'valid email' => array(
                    'rule' => 'email',
                    'message' => 'Nhập địa chỉ email hợp lệ'
                ),
                'duplicate email' => array(
                    'rule'=>'isUnique',
                    'message' => 'email đã có người sử dụng'
                ),
                'not empty' => array(
                    'rule' => 'notBlank',
                    'message' => 'Email không được để trống'
                ),
                'exist' => array(
            		'rule' => array('checkLogin','password' ), 
            		 'message' => 'Email hoặc mật khẩu không đúng'
            	)
            ),
          /*  'Login' => array(
            	'exist' => array(
            		'rule' => array('checkLogin','email','password' ), 
            		 'message' => 'Email hoặc mật khẩu không đúng'
            	)
            )*/
        );
     if($this->validates($this->validate))
	 return TRUE;
	 else
	 return FALSE;
 	}

	function checkLogin($username,$password){
     /*$sql = "Select login_id,login_pw from users where login_id = ?'$username' AND login_pw = '$password'";
     $this->query($sql, []);*/
     $result = $this->find('count', [
        'conditions' => ['login_id' => $username, 'login_pw' => $password]
    ]);
		//error_log(print_r($result, true), 3, '/www/htdocs/app/tmp/logs/debug.txt');
    if($result > 0){
       return TRUE;
     } else {
       return FALSE;
     }
   }
 }
?>