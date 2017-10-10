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
		// In config/routes.php
		use Cake\Routing\Route\DashedRoute;

		Router::scope('/', function ($routes) {
		    // Connect the generic fallback routes.
		    $routes->fallbacks(DashedRoute::class);
		});

		Phương thức connect() bao gồm 3 tham số 
			$routes->connect(
		    '/url/template',          // mẫu url 
		    ['default' => 'defaultValue'],  // controller, action, value
		    ['option' => 'matchingRegex'] // các biểu thức chính quy cho các phần tử 
		);
			Tham số đầu tiên; được sử dụng để nói cho router biết đường dẫn bạn đang muốn kiểm soát. Đường dẫn là một 
			chuỗi thông thường ngăn cách bằng dấu gạch chéo tuy nhiên có thể bao gồm dấu * đại diện cho route element 
		Bạn có thể sử dụng hai tham số của connect() để khai báo với CakePHP.
			$routes->connect(
		    '/pages/*',
		    ['controller' => 'Pages', 'action' => 'display']
			);
			request /pages/products sẽ được mapping tới PagesController->display('products');
			Ngoài việc sử dung 1 dấu *  ta có thể sử dụng 2 dấu ** để chỉ định phấn còn lại sẽ như là 1 đối số truyền vào
			duy nhất 
				Eg.   
					$routes->connect(
				    '/pages/**',
				    ['controller' => 'Pages', 'action' => 'show']
				);
			Ta có  request /pages/the-example-/-and-proof sẽ được mapping tói PagesController->show('the-example-/-and-proof')  
		Bạn có thể sử dụng hai tham số của phương thức Connect() để cung cấp bất kì tham số định tuyến nào bao gồm các giá trị
		định của router 
					$routes->connect(
				    '/government',
				    ['controller' => 'Pages', 'action' => 'display', 5]
					);
				Request /government sẽ được mapping với PagesController->display(5);
		Sử dụng chung đinh tuyến
					$routes->connect(
			 	   '/cooks/:action/*', ['controller' => 'Users']
					);
			Đoạn lênh trên nới với router bất cứ URL bắt đầu bằng cooks sẽ được mapping tới UsersController. hàm được gọi phụ
			thuộc vào :action và tham số truyển vào phụ thuộc vào * 
		Xây dựng mapping với các phương thức post get .. cụ thể 
					// Create a route that only responds to GET requests.
					$routes->get(
					    '/cooks/:id',
					    ['controller' => 'Users', 'action' => 'view'],
					    'users:view'
					);

					// Create a route that only responds to PUT requests
					$routes->put(
					    '/cooks/:id',
					    ['controller' => 'Users', 'action' => 'update'],
					    'users:update'
					);
			HTTP hepper cho: GET, POST, PUT, PATCH, DELETE, OPTIONS,HEAD
	2.1. Route Elements (Các thành phần của route)
			$routes->connect(
		    '/:controller/:id',
		    ['action' => 'view']
			)->setPatterns(['id' => '[0-9]+']);

			// Prior to 3.5 use the options array
			$routes->connect(
			    '/:controller/:id',
			    ['action' => 'view'],
			    ['id' => '[0-9]+']
			);
		Phần tử :Controller là một phần mặc định của Router CakePHP, do đó, bộ định tuyến biết làm thế nào để khớp và xác định các tên 
		bộ điều khiển trên URL. 
			use Cake\Routing\Route\DashedRoute;
			// Create a builder with a different route class.
			$routes->scope('/', function ($routes) {
			    $routes->setRouteClass(DashedRoute::class);
			    $routes->connect('/:controller/:id', ['action' => 'view'])
			        ->setPatterns(['id' => '[0-9]+']);

			    // Prior to 3.5 use options array
			    $routes->connect(
			        '/:controller/:id',
			        ['action' => 'view'],
			        ['id' => '[0-9]+']
			    );
			});
			

			Nếu bạn có một bộ điều khiển duy nhất trong ứng dụng của bạn và bạn không muốn tên điều khiển xuất hiện trong url, bạn có thể
			ánh xạ tất cả các URL vào hành động của home bộ điều khiển 
				ví dụ: như có các URL như /demo thay vì /home/demo 
				$routes->connect('/:action', ['controller' => 'Home']);
			Nếu bạn muốn cung cấp URL không phân biệt chữ hoa chữ thường, bạn có thể sử dụng các sửa đổi nội tuyến biểu thức chính quy
			// Prior to 3.5 use the options array instead of setPatterns()
				$routes->connect(
				    '/:userShortcut',
				    ['controller' => 'Teachers', 'action' => 'profile', 1],
				)->setPatterns(['userShortcut' => '(?i:principal)']);
			Eg2: 
				// Prior to 3.5 use the options array instead of setPatterns()
				$routes->connect(
				    '/:controller/:year/:month/:day',
				    ['action' => 'index']
				)->setPatterns([
				    'year' => '[12][0-9]{3}',
				    'month' => '0[1-9]|1[012]',
				    'day' => '0[1-9]|[12][0-9]|3[01]'
				]);
			Có một số yếu tố tuyến đường có ý nghĩa đặc biệt trong CakePHP và không được sử dụng trừ khi bạn muốn có ý nghĩa đặc biệt
			controller Được sử dụng để đặt tên bộ điều khiển cho một tuyến đường.
				action Được sử dụng để đặt tên thao tác điều khiển cho một tuyến đường.
				plugin Được sử dụng để đặt tên cho plugin một bộ điều khiển được đặt trong.
				prefixĐược sử dụng cho định tuyến tiền tố
				_extĐược sử dụng cho định tuyến tệp extentions .
				_baseĐặt để falseloại bỏ đường dẫn cơ sở từ URL được tạo ra. Nếu ứng dụng của bạn không nằm trong thư mục gốc, điều này có thể được sử dụng để tạo các URL có liên quan đến 'bánh tương đối'.
				_scheme Thiết lập để tạo liên kết trên các chương trình khác nhau như webcal hoặc ftp . Mặc định cho lược đồ hiện tại.
				_hostĐặt chủ nhà sử dụng cho liên kết. Mặc định cho máy chủ lưu trữ hiện tại.
				_port Đặt cổng nếu bạn cần tạo liên kết trên các cổng không chuẩn.
				_full Nếu truecác FULL_BASE_URL liên tục sẽ được thêm vào phía trước URL được tạo ra.
				# Cho phép bạn thiết lập các đoạn mã băm URL.
				_sslĐặt để truechuyển đổi URL được tạo ra sang https hoặc false để buộc http.
				_methodXác định động từ / phương thức HTTP để sử dụng. Hữu ích khi làm việc với Tạo RESTful Routes .
				_nameTên tuyến đường. Nếu bạn đã thiết lập các tuyến đường có tên, bạn có thể sử dụng khóa này để chỉ định nó.

	2.2. configuring Route options  (Tùy chọn cấu hình)
			$routes->connect(
			'/:lang/articles/:slug',
			    ['controller' => 'Articles', 'action' => 'view'],
			)
			// Allow GET and POST requests.
			->setMethods(['GET', 'POST'])

			// Only match on the blog subdomain.
			->setHost('blog.example.com')

			// Set the route elements that should be converted to passed arguments
			->setPass(['slug'])

			// Set the matching patterns for route elements
			->setPatterns([
			    'slug' => '[a-z0-9-_]+',
			    'lang' => 'en|fr|es',
			])

			// Also allow JSON file extensions
			->setExtensions(['json'])

			// Set lang to be a persistent parameter
			->setPersist(['lang']);
	2.3. Passing Parameters to Action - Vượt qua tham số để hành động 
			// src/Controller/BlogsController.php
			public function view($articleId = null, $slug = null)
			{
			    // Some code here...
			}

			// routes.php
			Router::scope('/', function ($routes) {
			    $routes->connect(
			        '/blog/:id-:slug', // E.g. /blog/3-CakePHP_Rocks
			        ['controller' => 'Blogs', 'action' => 'view']
			    )
			    // Define the route elements in the route template
			    // to pass as function arguments. Order matters since this
			    // will simply map ":id" to $articleId in your action
			    ->setPass(['id', 'slug'])
			    // Define a pattern that `id` must match.
			    ->setPatterns([
			        'id' => '[0-9]+',
			    ]);
			});
		Bây giờ nhờ các khả năng định tuyến ngược, bạn có thể truyền mảng URL như ví dụ dưới và CakePHP sẽ tạo được URL như được định nghĩa trong các Router
				// view.ctp
				// This will return a link to /blog/3-CakePHP_Rocks
				echo $this->Html->link('CakePHP Rocks', [
				    'controller' => 'Blog',
				    'action' => 'view',
				    'id' => 3,
				    'slug' => 'CakePHP_Rocks'
				]);

				// You can also used numerically indexed parameters.
				echo $this->Html->link('CakePHP Rocks', [
				    'controller' => 'Blog',
				    'action' => 'view',
				    3,
				    'CakePHP_Rocks'
				]);
	2.4. Using Named Routes
				// Connect a route with a name.
				$routes->connect(
				    '/login',
				    ['controller' => 'Users', 'action' => 'login'],
				    ['_name' => 'login']
				);

				// Name a verb specific route (3.5.0+)
				$routes->post(
				    '/logout',
				    ['controller' => 'Users', 'action' => 'logout'],
				    'logout'
				);

				// Generate a URL using a named route.
				$url = Router::url(['_name' => 'logout']);

				// Generate a URL using a named route,
				// with some query string args.
				$url = Router::url(['_name' => 'login', 'username' => 'jimmy']);

		Nếu Route của bạn chúa bất cứ thành phần nào như :controller bạn cần cung cấp làm 1 phần của các tùy chọn Router::url()
		Khi xây dựng tên cho các Route, bạn sẽ gắn với một số quy ước tên. CakePHP giúp dây dựng tên Route dễ dàng bằng cách cho
		phép bạn định nghĩa các tiền tố tên trong mỗi phạm vi.
				Router :: scope ( '/api' ,  [ '_namePrefix'  =>  'api:' ],  function  ( $routes )  { 
	    // Tên của tuyến đường này sẽ là `api: ping` 
				$ routes -> get ( '/ping' ,  [ 'controller'  =>  'Pings' ],  'ping' ); 
				}); 
				// Tạo ra một URL cho tuyến đường ping 
				Router :: url ([ '_name'  =>  'api: ping' ]);

				// Sử dụng tênPrefix với plugin () 
				Router :: plugin ( 'Contacts' ,  [ '_namePrefix'  =>  'contacts:' ],  function  ( $routes )  { 
				    // Kết nối các tuyến đường. 
				});

				// Hoặc với tiền tố () 
				Router :: tiền tố ( 'Admin' ,  [ '_namePrefix'  =>  'admin:' ],  function  ( $routes )  { 
				    // Kết nối các tuyến đường. 
				});
		Bạn cũng có thể sử dụng _namePrefix lồng nhau:
		Router::plugin('Contacts', ['_namePrefix' => 'contacts:'], function ($routes) {
	    $routes->scope('/api', ['_namePrefix' => 'api:'], function ($routes) {
	        // This route's name will be `contacts:api:ping`
	        $routes->get('/ping', ['controller' => 'Pings'], 'ping');
		    });
		});
		// Generate a URL for the ping route
		Router::url(['_name' => 'contacts:api:ping']);
	2.5. Prefix Routing (Định tuyến tiền tố)
		Nhiều ứng dụng yêu cầu 1 phần quản trị mà người dùng được đặc quyền có thể thực hiện thay đổi. Điều này thường được thực hiện 
		thông qua một url đặc biệt như /admin/users/edit/5
		Trong php định tuyến tiền tố có thể được kích hoạt bằng cách enable prefix scope method
			use Cake\Routing\Route\DashedRoute;
			Router::prefix('admin', function ($routes) {
			    // All routes here will be prefixed with `/admin`
			    // And have the prefix => admin route element added.
			    $routes->fallbacks(DashedRoute::class);
			});
		Khi tạo cá prefix Routing bạn có thể đặt các tham số tuyến đường bổ sung bằng cách sử dụng $options đối số 
			Router :: prefix ( 'admin' ,  [ 'plugin'  =>  'DebugKit' ),  function  ( $routes )  { 
			    // Những tuyến kết nối ở đây được đặt trước bằng '/ admin' và 
			    // có thiết lập phím định tuyến 'param'. 
			    $ routes -> connect ( '/: controller' ); 
			});
			Bạn cũng có thể xác định các tiền tố bên trong các phạm vi plugin
				Router::plugin('DebugKit', function ($routes) {
				    $routes->prefix('admin', function ($routes) {
				        $routes->connect('/:controller');
				    });
				});	
			Bạn có thể xếp nhiều tiền tố nếu cần 
				Router::prefix('manager', function ($routes) {
				    $routes->prefix('admin', function ($routes) {
				        $routes->connect('/:controller');
				    });
				});
					manager/admin

			Khi sử dụng các tuyến tiền tố điều quan trọng nhất là phải đặt tùy chọn tiền tố. Dưới đâu là cách tạo liên kết này bằng cách
			sử dụng trình trợ giúp HTML 
				// Go into a prefixed route.
				echo $this->Html->link(
				    'Manage articles',
				    ['prefix' => 'manager', 'controller' => 'Articles', 'action' => 'add']
				);

				// ĐỂ LẠI TIỀN TỐ 
				echo $this->Html->link(
				    'View Post',
				    ['prefix' => false, 'controller' => 'Articles', 'action' => 'view', 5]
				);
	2.6. Plugin Routing - Định tuyến plugin
				Router :: plugin ( 'DebugKit' ,  function  ( $ routes )  { 
			    // Các tuyến kết nối ở đây được đặt trước với '/ debug_kit' và 
			    // có phần tử đường dẫn plugin được thiết lập để 'DebugKit'. 
			    $ Routes -> connect ( '/: bộ điều khiển ' ); 
					});
			Khi tạo phạm vi plugin, bạn có thể tùy chỉnh phần tử đường dẫn sử dụng với path tùy chọn
				Router :: plugin ( 'DebugKit' ,  [ 'path'  =>  '/ debugger' ],  function  ( $ routes )  { 
			    // Các tuyến kết nối ở đây được đặt trước bằng '/ debugger' và 
			    // có phần tử đường dẫn plugin được thiết lập là ' DebugKit '. 
			    $ Routes -> connect ( ' /: controller ' ); 
				});
			Tạo liên kết tới đường dẫn Plugin
				echo  $ this -> Html -> link ( 
			    'New todo' , 
			    [ 'plugin'  =>  'Todo' ,  'controller'  =>  'TodoItems' ,  'action'  =>  'create' ] 
				);
				Tạo liên kết không có plugin
					echo $this->Html->link(
					    'New todo',
					    ['plugin' => null, 'controller' => 'Users', 'action' => 'profile']
					);
	2.7. SEO - friendly Routing
		Một số nhà phát triển muốn sử dụng dấu gạch ngang trong URL, vì nó được cho là có thứ hạng tốt hơn cho công cụ tìm kiếm
			use Cake\Routing\Route\DashedRoute;
			Router::plugin('ToDo', ['path' => 'to-do'], function ($routes) {
			    $routes->fallbacks(DashedRoute::class);
			});
	2.8. Matching specific HTTP method
				Router::scope('/', function($routes) {
			    // This route only matches on POST requests.
			    $routes->post(
			        '/reviews/start',
			        ['controller' => 'Reviews', 'action' => 'start']
			    );

			    // Match multiple verbs
			    // Prior to 3.5 use $options['_method'] to set method  // trước bản 3.5
			    $routes->connect(
			        '/reviews/start',
			        [
			            'controller' => 'Reviews',
			            'action' => 'start',
			        ]
			    )->setMethods(['POST', 'PUT']);
				});
		Bạn có thể kết hợp nhiều phương pháp HTTP bằng cách sử dụng một mảng. Bởi vì _method tham số là khoá định tuyến, nó tham 
		gia vào cả việc phân tách URL và tạo URL. Để tạo URL cho các tuyến đường cụ thể theo phương pháp, bạn sẽ cần bao 
		gồm _method khóa khi tạo URL:
				$url = Router::url([
				    'controller' => 'Reviews',
				    'action' => 'start',
				    '_method' => 'POST',
				]);
	2.9. Matching specific Hostnames
	2.10. Routing File Extensions
			Router :: extensions ([ 'json' ,  'xml' )); // global

			Router :: scope ( '/' ,  function  ( $ routes )  {      
			    // Trước khi dùng 3.5.0 `extensions ()` 
			    $ routes -> setExtensions ([ 'json' ,  'xml' )); 
			});

		Eg full;
			Router::scope('/page', function ($routes) {
			    // Prior to 3.5.0 use `extensions()`
			    $routes->setExtensions(['json', 'xml', 'html']);
			    $routes->connect(
			        '/:title',
			        ['controller' => 'Pages', 'action' => 'view']
			    )->setPass(['title']);
			});
	2.11. Connecting Scoped Middleware (****)
		// in config/routes.php
			use Cake\Http\Middleware\CsrfProtectionMiddleware;
			use Cake\Http\Middleware\EncryptedCookieMiddleware;

			Router::scope('/', function ($routes) {
			    $routes->registerMiddleware('csrf', new CsrfProtectionMiddleware());
			    $routes->registerMiddleware('cookies', new EncryptedCookieMiddleware());
			});

		Once registed
			$routes->scope('/cms', function ($routes) {
			    // Enable CSRF & cookies middleware
			    $routes->applyMiddleware('csrf', 'cookies');
			    $routes->get('/articles/:action/*', ['controller' => 'Articles'])
			});

	2.12. Grouping Middleware (****)
		$routes->registerMiddleware('cookie', new EncryptedCookieMiddleware());
		$routes->registerMiddleware('auth', new AuthenticationMiddleware());
		$routes->registerMiddleware('csrf', new CsrfProtectionMiddleware());
		$routes->middlewareGroup('web', ['cookie', 'auth', 'csrf']);

		// Apply the group
		$routes->applyMiddleware('web');
3. Creating RESTful Routes
	Creating Nested Resource Routes
	Limiting the Routes Created
	Changing the Controller Actions Used
	Mapping Additional Resource Routes
	Custom Route Classes for Resource Routes
	URL Inflection for Resource Routes
	Changing the Path Element
4. Passed Arguments
	Default Route Class
	Fallbacks Method
5. Generating URLs
6. Redirect Routing
7. Custom Route Classes
8. Creating Persistent URL Parameters
9. Handling Named Parameters in URLs
							        =================================================
										=====================================
												 ___          _           
												| _ \___ _  _| |_ ___ _ _ 
												|   / _ \ || |  _/ -_) '_|
												|_|_\___/\_,_|\__\___|_|  
							            =====================================
							        ================================================'  