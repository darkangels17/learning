<?php
class Training extends AppModel{
	  function validateUser(){
	    $this->validate = array(
	        'userName' => [
	          'not empty' => [
	              'rule' => 'notBlank',
	              'message' => 'Tên người dùng không được để trống '
	          ],
	          'Unique' => [
	              'rule' => 'isUnique',
	              'message' => 'Tên người dùng đã có người sử dụng'
	          ],
	          'not Special' => [
	              'rule' => '/^[a-z A-Z]{1,255}$/i',
	              'message' => 'Tên không được chứa kí tự đặc biệt và số'
	          ]
	        ],
            'password' => [
                'not empty' => [
                    'rule' => 'notBlank',
                    'message' => 'Mật khẩu không được để trống'
                ],
                'pass Length' => [
                    'rule' => ['lengthBetween',6,8],
                    'message'=> 'Mật khẩu phải từ 6 đến 8 kí tự'
                ]
            ],
	        'confirmPassword' => [
	            'equalTo' => [
	                'rule'=>['equalPassToConfirmPass'],
	                'message' => 'Mật khẩu xác nhận không trùng với mật khẩu'
	            ]
	        ],
            'email' => [
                'not empty' => [
                    'rule' => 'notBlank',
                    'message' => 'Email không được để trống'
                ],
                'valid email' => [
                    'rule' => 'email',
                    'message' => 'Nhập địa chỉ email hợp lệ'
                ],
                'Unique' => [
	              'rule' => 'isUnique',
	              'message' => 'Email đã có người sử dụng'
	            ]
            ],
	        'emailLogin'=>[
	            'not empty' => [
	                'rule' => 'notBlank',
	                'message' => 'Email không được để trống'
	            ],
	            'valid email' => [
	                'rule' => 'email',
	                'message' => 'Nhập địa chỉ email hợp lệ'
	            ],
	        ],
	        'emailEdit'=>[
	            'not empty' => [
	                'rule' => 'notBlank',
	                'message' => 'Email không được để trống'
	            ],
	            'not Duplicate' =>[
	                'rule' => 'checkEmailEdit',
	                'message' => 'Email đã có người sử dụng'
	            ]
	        ],
	        'address' => [
	            'not empty' => [
                    'rule' => 'notBlank',
                    'message' => 'Địa chỉ không được để trống'
                ],
	            'max Length' => [
	                'rule' => ['maxLength',50],
	                'message' => 'Địa chỉ không quá 50 kí tự' 
	            ]
	        ],
	        'birthday'=>[
	            'format' => [
	                'rule'=>['date','dmy'],
	                'message' => 'Ngày sinh phải đúng và nhập theo format d-m-y hoặc d/m/y'
	            ]
	            
	        ],
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
  	function checkEmailEdit(){
 	    $totalRecord = $this->field('count',[
 	       'conditions'=>['Email'=>$this->data['Training']['emaiEdit']]   // chứa làm khác 
 	    ]);
 	}
    /**
     *  hàm kiểm tra email và password trong database
     */
	function checkLogin(){
	 $password = md5($this->data['Training']['password']);
     $result = $this->find('count', [
        'conditions' => ['Email' => $this->data['Training']['emailLogin'], 'Password' => $password]
    ]);
    if($result > 0){
       return TRUE;
     } else {
       return FALSE;
     }
   }
   /**
    * đối chiếu pass và confirm pass
    * @return boolean
    */
    function equalPassToConfirmPass(){
        if($this->data['Training']['password'] == $this->data['Training']['confirmPassword']) {
            return true;
        } else {
            return false;
        }
    }
   /**
    * lấy tổng số người dùng
    * @return tổng số người dùng 0 nếu không có người dùng 
    */
   function countListUser() {
       $total = $this->find('count');
       return $total;
   }
   /**
    * kiểm tra xem userId có tồn tại không
    * @param  $id mã người dùng cần kiểm tra.
    * @return boolean true nếu tồn tại trong database false nếu không tồn tại
    */
   function exsistUser($id){
       $total = $this->field('count',[
           'conditions' => ['id'=>$id]
       ]);
       if($total > 0){
           return true;
       }
       return FALSE;
   }
   /**
    * lấy thông tin người dùng từ id
    * return: thông tin người dùng
    */
   function getUserById($id){
       $user = $this->find('first',[
           'fields'=>['userName','email','birthday','address','type'],
           'conditions' => ['id'=>$id]
           ]
           );
       return $user;
   }
 }
?>