
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
6. Load Additional model 
		Controller::loadModel(String $modelClass, String type );
		- Phương thức loadModel() tiện dụng khi bạn cần phải sử dụng một mô hình table/colection mà không phải của một controller mặc định 

								========================================================================
											====================================================
											
												  ___|             |             | |          
												 |      _ \  __ \  __|  __| _ \  | |  _ \  __|
												 |     (   | |   | |   |   (   | | |  __/ |   
												\____|\___/ _|  _|\__|_|  \___/ _|_|\___|_|   
											====================================================
								========================================================================