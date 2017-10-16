<?php
class TrainingsController extends AppController {
	public $name = "Trainings";
	var $component = array("Session");
	/* function beforeFilter(){
	    parent::beforeFilter();
	} */
	/**
	 * kiểm tra đăng nhập
	 */
	function login() {
		$err = "";
		$training = $this->data;
		$this->Training->set($training);
		if($training){
			if($this->Training->validateLogin()== TRUE) { 
			    $id = $this->Training->getIdByEmail($training['Training']['email']);
			    $this->Session->write("id",$id);
			    //$this->Session->delete('id');
				$this->redirect('index');
			} 
		}
	}
	/**
	 * lấy danh sách và phân trang 
	 */
	function index(){
	   $id = $this->Session->read('id');
	   if(!isset($id)) {
	       $this->redirect(['action'=>'login']);
	       return;
	   }
	   $type = $this->Training->getTypeById($id);
	   $emailSearch = "";
	   if(isset($_POST['Email'])) {
	       $emailSearch = $_POST['Email'];
	   }
	   $this->set("emailSearch", $emailSearch);
	   $emailSearch = str_replace('%',  '\%',  $emailSearch);
	   $emailSearch = str_replace('_',  '\_',  $emailSearch);
	   $emailSearch = '%'.$emailSearch.'%';
	   $total = $this->Training->countListUser($type,$emailSearch);
	   $this->set('total',$total);
	   if($total > 0){
	      if($type == TRUE) {
    	      $this-> paginate = [
                  'fields' => ['id','userName','email','birthday','address','type'],
                  'limit' => 3,
    	          'conditions' => ['email LIKE' => $emailSearch],
                  'order' =>  ['id' => 'ASC'],
             ];
	      } else {
	          $this-> paginate = [
	              'fields' => ['id','userName','email','birthday','address','type'],
	              'conditions' =>['type'=>$type, 'email LIKE' =>$emailSearch],
	              'limit' => 3,
	              'order' =>  ['id' => 'ASC'],
	          ];
	      }
	     $arrUser = $this->paginate("Training");
         $this->set("listUser",$arrUser);
         $this->set("typeLogin",$type);
	   }
	}
	/**
	 * thêm User
	 */
	function add(){
	    $idLogin = $this->Session->read('id');
	    if(!isset($idLogin)) {
	        $this->redirect(['action'=>'login']);
	        return;
	    }
	    if($this->Training->getTypeById($idLogin)!= 1) {
	        $this->redirect(['action'=>'index']);
	        return;
	    }
	    $data = $this->data;
	    $this->Training->set($data);
	    if($data && $this->Training->validateAdd()== TRUE) {
    	      $data['Training']['password'] = md5($data['Training']['password']);
    	      $birthday = $data['Training']['birthday'];
    	      $data['Training']['birthday'] = date('Ymd',strtotime($birthday));
             if($this->Training->save($data,false)) {
                 $this->redirect(['action'=>'index']);
             } else {
                 $this->set('error','Hệ thống có lỗi xin vui lòng thử lại sau ít phút');
             }
    	} 
	}
	/**
	 * kiểm tra edit
	 */
	function edit(){
	    $idUserLogin = $this->Session->read('id');
	    if(!isset($idUserLogin)) {
	        $this->redirect(['action'=>'login']);
	        return;
	    }
	    $id = $this->request->query('id');
	    $id += 0;
	    if(is_integer($id) && $this->Training->exsistUser($id)) {
	        $type = $this->Training->getTypeById($idUserLogin);
	        // người dùng đăng nhập đánh url để edit admin hệ thống sẽ báo id không tồn tại 
	        if($type !=1 && $this->Training->getTypeById($id) ==1) {
	            $this->set("error",'id không tồn tại');
	            return;
	        }
	        $readOnly = TRUE;
	        if($type == TRUE || $id == $idUserLogin){
	            $readOnly = FALSE;
	        }
	        $this->set("readOnly",$readOnly);
	        // kiểm tra nếu người đúng click button Update
	        if(isset($_POST['Update'])&& !$readOnly) {
	            $data = $this->data;
	            $this->Training->set($data);
	            if($data && $this->Training->validateEdit()== TRUE ) {
	                $birthday = $data['Training']['birthday'];
	                $data['Training']['birthday'] = date('Ymd',strtotime($birthday));
	                $data['Training']['email'] =  $data['Training']['email'] ;
	                
	                if($this->Training->exsistUser( $data['Training']['id'])) {
	                    if($this->Training->save($data,false)) {
	                        $this->redirect(['action'=>'index']);
	                    } else {
	                        $this->set('error','Hệ thống có lỗi xin vui lòng thử lại sau ít phút');
	                    }
	                } else {
	                    $this->set('error','id không còn tồn tại');
	                }
	                
	            } else {
	                $user = ['Training'=>['id'=>$data['Training']['id'],
	                    'email' => $data['Training']['email'],
	                    'userName'=>$data['Training']['userName'],
	                    'birthday'=>$data['Training']['birthday'],
	                    'address'=>$data['Training']['address'],
	                    'type' => $data['Training']['type']
	                ]
	                ];
	                $this->set('user',$user);
	            }
	        } else {
	            $user = $this->Training->getUserById($id);
	            $user['Training']['birthday'] = date("d-m-Y",strtotime($user['Training']['birthday']));
	            $this->set('user',$user);
	        }
	    } else {
	            $this->set("error",'id không tồn tại');
	    }
	}
	/**
	 * xóa người dùng
	 */
	function delete() {
             $idLogin = $this->Session->read('id');
             if(!isset($idLogin)) {
                 $this->redirect(['action'=>'login']);
                 return;
             }
             if($this->Training->getTypeById($idLogin)!= 1) {
                 $this->redirect(['action'=>'index']);
                 return;
             }
	        $id = $this->request->query('id');
	        $id += 0;
	        if(is_integer($id) && $this->Training->exsistUser( $id)) {
	            if(isset($_POST['Delete'])) {
	                    if($this->Training->delete($id)) {
	                        $this->redirect(['action'=>'index']);
	                    } else {
	                        $this->set('error','Hệ thống có lỗi xin vui lòng thử lại sau ít phút');
	                    }   
	            } else {
    	            $user = $this->Training->getUserById($id);
    	            $user['Training']['birthday'] = date("d-m-Y",strtotime($user['Training']['birthday']));
    	            $this->set('user',$user);
	            }
	        } else {
	            $this->set("error",'id không tồn tại');
	        }
	    }
}
?>