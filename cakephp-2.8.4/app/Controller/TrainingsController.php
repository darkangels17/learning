<?php
class TrainingsController extends AppController {
	public $name = "Trainings";
	var $component = array("Session");
	/**
	 * kiểm tra đăng nhập
	 */
	function login() {
		$err = "";
		$training = $this->data;
		$this->Training->set($training);
		if($training){
			if($this->Training->validateUser()== TRUE) {
				$this->Session->write("session",$training['Training']['emailLogin']);
				$this->redirect('index');
			} 
		}
	}
	/**
	 * lấy danh sách và phân trang 
	 */
	function index(){
	   $total = $this->Training->countListUser();
	   $this->set('total',$total);
	   if($total > 0){
	      $this-> paginate = [
              'fields' => ['id','userName','email','birthday','address','type'],
              'limit' => 3,
              'order' =>  ['id' => 'ASC']
         ];
	     $arrUser = $this->paginate("Training");
         $this->set("listUser",$arrUser);
	   }
	}
	/**
	 * thêm User
	 */
	function add(){
	    $data = $this->data;
	    $this->Training->set($data);
	    if($data && $this->Training->validateUser()== TRUE) {
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
	
	function edit(){
	    if(isset($_POST['Update'])) {
	        $data = $this->data;
	        $this->Training->set($data);
	        if($data && $this->Training->validateUser()== TRUE ) {
	            $birthday = $data['Training']['birthday'];
	            $data['Training']['birthday'] = date('Ymd',strtotime($birthday));
	            if($this->Training->save($data,false)) {
	                $this->redirect(['action'=>'index']);
	            } else {
	                $this->set('error','Hệ thống có lỗi xin vui lòng thử lại sau ít phút');
	            }
	        }
	    } else {
	        $id = $this->request->query('id');
	        $id += 0;
	        if(is_integer($id)) {
	            $user = $this->Training->getUserById($id);
	            $user['Training']['birthday'] = date("d-m-Y",strtotime($user['Training']['birthday']));
	            $this->set('user',$user);
	        } else {
	            $this->set("error",'Không tồn tại id trong database');
	        }
	    }
	  
	}
}
?>