
								========================================================================
											====================================================
											
												  ___|             |             | |          
												 |      _ \  __ \  __|  __| _ \  | |  _ \  __|
												 |     (   | |   | |   |   (   | | |  __/ |   
												\____|\___/ _|  _|\__|_|  \___/ _|_|\___|_|   
											====================================================
								========================================================================
1. The App controller
	- Đây là lớp cha cho tất cả controller của bạn. AppController bản thân nó mở rộng từ Cake\Controller\Controller lớp bao gồm trong CakePHP
	- Chứa các phương thức mà các Controller thường xuyên sử dụng tới 
2. 	Luồng di chuyển khi có request
	- Khi có một yêu cầu gửi từ ứng dụng CakePHP. Lớp Cake\Routing\Router and Cake\Routing\Dispatcher sẽ sử dụng Connecting Routes để tìm các điều 
	khiển chính xác.
3. Action Controller 
	- Chuyển đổi các tham số yêu cầu thành phản hồi cho trình duyệt/ người thực hiện yêu cầu. CakePHP sử dụng các quy ước để tự động hóa quá trình
	này và laoij bỏ một số mã boilerplate mà bạn cần phải viết.
	- Theo quy ước CakePHP đưa ra một chế độ xem có phiên bản biến thể của tên hành động. 
	Ví dụ. RecipesController có thể chứa view(), share(), search() trong src/Controller/RecipesController.php các tệp hiển thị cho các mục này sẽ là 
	src/Template/Recipes/view.ctp, src/Template/Recipes/share.ctp, src/Template/Recipes/search.ctp. Do các quy ước mà CakePHP sử dụng, bạn không cần
	hiển thị chế độ xem theo cách thủ công. Thay vào đó, một khi hành động của controller hoàn thành, CakePHP sẽ xử lý việc hiển thị và phân phối view
4. Interacting with Views // Tương tác với View
	Controller::set();
		$this->set("Variable name", $value);
	4.1 Setting View Variables
	// First you pass data from the controller:
		$this->set('color', 'pink');
		// Then, in the view, you can utilize the data:
		?>
			You have selected <?= h($color) ?> icing for the cake.

			function h($string|array|object $text) đoạn text sẽ được bao quanh bởi các kí tự đặc biệt của html
			=> dự đoán excape html 
	4.2. Thiết lập tùy chọn View
		- Nếu bạn muốn tùy chỉnh xem lớp, layout/template 
			$ this -> viewBuilder () 
				    -> helpers ([ 'MyCustom' ]) 
				    -> theme ( 'Modern' ) 
				    -> className ( 'Modern.Admin' );
	4.3. Rendering a View // Hiển thị chế độ xem
		- Controller::render(String $view, String $layout)
		- Là phương thức được tự động gọi vào cuối mỗi hành động điều khiển yêu cầu. Phương thức này thực hiện tất cả các logic xem( sử dụng dữ liệu bạn đã
		gửi bằng cách sử dụng Controller::set()), đặt chế độ xem bên trong của nó View::$layout và phục vụ nó cho người dùng cuối 
		***** Thiết lập đường dẫn gọi view khác với mặc định 
					b1. $this->autoRender = false; // ngăn phương thức Render() tự động gọi
					b2. $this->Render("/Users/demo") // demo.ctp in Users 
5. Redirecting to Other Pages // Chuyển hướng tói trang khác 
	Controller::redirect(string| array $url, Integer $status)  phương pháp này lấy thông sô đầu tiên dưới dạng URL tương đối của CakePHP => chuyển tới màn hình nhận
		public function place_order()
		{
		    return $this->redirect(
		        ['controller' => 'Orders', 'action' => 'confirm']
		    );
		}
		ta có OrdersController->confirm();
	Bạn cũng có thể dử dụng một url tuyệt đối làm tham số url;
		return $this->redirect('/Orders/confirm');
		return this->redirect('http://www.24h.com.vn');
	Bạn cũng có thể chuyển dữ liệu cho hành động 
		retrun $this->redirect(['action' => 'test', 15]);
		ta có gọi phương thức với tham số truyền vào là 15 test(15) ở cùng controller 
	Tham số thứ hai của redirect() cho phép bạn xác định mã trạng thái HTTTP để đi kèm với chuyển hướng
	    vdu: 301, 303
	Nếu bạn cần chuyển hướng đến trang giới thiệu bạn có thể sử dụng
		return $this->redirect($this->referer());
	Ví dụ sử dụng chuỗi truy vấn và hash
		return $this->redirect([
		    'controller' => 'Orders',
		    'action' => 'confirm',
		    '?' => [
		        'product' => 'pizza',
		        'quantity' => 5
		    ],
		    '#' => 'top'
		]);
		ta có đường dẫn  http://www.example.com/orders/confirm?product=pizza&quantity=5#top
	5.1. Redirecting to Another Action on the Same Controller // chuyển hướng tới hành động khác cùng trang điều khiển 
		Controller::setAction($ action,$args ...);
		Nếu bạn cần chuyển tiếp hành động hiện tại sang hành động khác trên cùng một Controller 
			$this->setAction(['action'=>'actionOther']);
6. Load Additional Model 
		Controller::loadModel(String $modelClass, String type );
		- Phương thức loadModel() tiện dụng khi bạn cần phải sử dụng một mô hình table/colection mà không phải của một controller mặc định 
			// Trong một phương pháp điều khiển. 
				$ this -> loadModel ( 'Articles' ); 
				$ recentArticles  =  $ this -> Articles -> find ( 'tất cả' ,  [ 
				    'limit'  =>  5 , 
				    'order'  =>  'Articles.created DESC' 
				]);
		- Nếu bạn đang sử dụng một nhà cung cấp bảng khác với ORM được xây dựng, bạn có thể liên kết hệ thống bảng đó vào bộ điều khiển của 
		CakePHP 
				// Trong một phương pháp điều khiển. 
				$ this -> modelFactory ( 
				    'ElasticIndex' , 
				    [ 'ElasticIndexes' ,  'factory' ] 
				);
		- Sau khi đăng kí bạn có thể sử dụng loadModel
				// Trong một phương pháp điều khiển. 
				$ this -> loadModel ( 'Locations' ,  'ElasticIndex' );
7. Paginating a Model
	Controller::paginate();
	Phương pháp này được sử dụng để phân trang các kết quả
		     $this->paginate = array(
		       'limit' => 4,// mỗi page có 4 record
		       'order' => array('id' => 'desc'),//giảm dần theo id
		     );
		     $data = $this->paginate("Book");
		     $this->set("data",$data);
8. Configuring Componets to Load //Cấu hình các thành phần để tải 
	Controller::loadComponet($name, $config = []);
		public function initialize()
		{
		    parent::initialize();
		    $this->loadComponent('Csrf');
		    $this->loadComponent('Comments', Configure::read('Comments'));
		}
		https://book.cakephp.org/3.0/en/controllers/components.html#configuring-components
		http://nongdanit.info/php-mysql/cakephp-bai-9-component-cach-viet-mot-component-trong-cakephp.html
9. Configuring Helpers to Load  
	Để sử dụng các lớp MVC bổ sung
	class RecipesController extends AppController
	{
	    public $helpers = ['Form']; // Form là tên ClassHelper 
	}

	https://book.cakephp.org/3.0/en/views/helpers.html#configuring-helpers  : xem để hiểu cấu hình helpper cho 3.0
	http://nongdanit.info/php-mysql/cakephp-bai-10-helper-tao-mot-helper-trong-cakephp.html
10. request Life - cycle Callback
	Bộ diều khiển CakePHP kích hoạt một số sự kiện, gọi lại mà bạn có thể sử dụng để chèn logic xung quanh vòng đời 
 10.1 Danh sách sự kiện 
 	Controller.initialize
 	Controller.startup
 	Controller.beforeRender
 	Controller.beforeRedirect
 	Controller.beforeShutdown
 10.2 Các phương pháp gọi lại của controller
  		Controller::beforeFilter(Event $event);
  		Cake\Controller\Controller::afterFilter(Event $event)


 https://book.cakephp.org/3.0/en/controllers.html

								========================================================================
											====================================================
											
												  ___|             |             | |          
												 |      _ \  __ \  __|  __| _ \  | |  _ \  __|
												 |     (   | |   | |   |   (   | | |  __/ |   
												\____|\___/ _|  _|\__|_|  \___/ _|_|\___|_|   
											====================================================
								========================================================================