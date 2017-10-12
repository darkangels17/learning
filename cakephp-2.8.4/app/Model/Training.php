<?php
class Training extends AppModel{
	  function validateLogin(){
	    $this->validate = array(
            'password' => array(
                'not empty' => array(
                    'rule' => 'notBlank',
                    'message' => 'Mật khẩu không được để trống'
                )
            ),
            'email' => array(
                'not empty' => array(
                    'rule' => 'notBlank',
                    'message' => 'Email không được để trống'
                ),
                'valid email' => array(
                    'rule' => 'email',
                    'message' => 'Nhập địa chỉ email hợp lệ'
                )
            ),
	        'checkExist' => array(
	            'exist' => array(
	                'rule' => array('checkLogin'), 
            		'message' => 'Email hoặc mật khẩu không đúng'
	            )
	        )
        );
     if($this->validates($this->validate))
	 return TRUE;
	 else
	 return FALSE;
 	}
    /**
     *  hàm kiểm tra email và password trong database
     */
	function checkLogin(){
	 $password = md5($this->data['Training']['password']);
     $result = $this->find('count', [
        'conditions' => ['Email' => $this->data['Training']['email'], 'Password' => $password]
    ]);
    if($result > 0){
       return TRUE;
     } else {
       return FALSE;
     }
   }
   /**
    * lấy danh sách 
    */
   function getListUser() {
      $arrUser = $this->find('all', [
          'fields' => ['UserId','UserName','Email','Birthday','Address','Type']
      ]);
      return  $arrUser;
   }
 }
?>