								=================================================
									=====================================
											 ___          _           
											| _ \___ _  _| |_ ___ _ _ 
											|   / _ \ || |  _/ -_) '_|
											|_|_\___/\_,_|\__\___|_|  
						            =====================================
						        ================================================'  
1. Quick Tour
	Hướng dẫn cách cấu hình CakePHP phổ biến nhất trong file 'routes.php'
	Lớp Router cung cấp hai giao diện dành cho kết nối routes 
		- Phương thức static là giao diện tương thích ngược lại ? 
		- The scoped builder cung cấp cú pháp ngắn gọn hơn khi xây dựng nhiều tuyến đường và hiệu suất tốt hơn

		use Cake\Routing\Router;
		// Using the scoped route builder.
		Router::scope('/', function ($routes) {
		    $routes->connect('/', ['controller' => 'Articles', 'action' => 'index']);
		});

		// Using the static method.
		Router::connect('/', ['controller' => 'Articles', 'action' => 'index']);
	Eg 1. 
		$routes->connect('/articles/*', ['controller' => 'Articles', 'action' => 'view']);
		/articles/15 sẽ tương ứng ArticlesController->view(15);
		Để kiểm tra biến đầu vào ta có thể sử dụng 
		$routes->connect(
		    '/articles/:id',
		    ['controller' => 'Articles', 'action' => 'view'],
		)
		->setPatterns(['id' => '\d+'])     
		->setPass(['id']);

		// Prior to 3.5 use the options array
		$routes->connect(
		    '/articles/:id',
		    ['controller' => 'Articles', 'action' => 'view'],
		    ['id' => '\d+', 'pass' => ['id']]
		);
	CakePHP Router có thể đảo ngược con đường. Tức là từ các mảng thông số phù hợp tạo ra được chuỗi URL
		use Cake\Routing\Router;
		echo Router::url(['controller' => 'Articles', 'action' => 'view', 'id' => 15]);
		// Will output
		/articles/15
	* Các Routes có thể được gắn nhãn duy nhất( Đặt tên duy nhất) để có thể tham chiếu nhanh chóng đến nó 
	thay vì tạo các tham số 
		// In routes.php
		$routes->connect(
		    '/login',
		    ['controller' => 'Users', 'action' => 'login'],
		    ['_name' => 'login']
		);

		use Cake\Routing\Router;
		echo Router::url(['_name' => 'login']);
		// Will output
		/login
	* chỉ dẫn tới thứ mục plugin và tìm các controller ở trong Blog để xử lý  
			Router::scope('/blog', ['plugin' => 'Blog'], function ($routes) {
		    $routes->connect('/', ['controller' => 'Articles']);
			});
		=> Blog\Controller\ArticlesController::index().
2. Connecting Routes

							        =================================================
										=====================================
												 ___          _           
												| _ \___ _  _| |_ ___ _ _ 
												|   / _ \ || |  _/ -_) '_|
												|_|_\___/\_,_|\__\___|_|  
							            =====================================
							        ================================================'  