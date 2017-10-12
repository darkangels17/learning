
I. Request
	1.1. Request Parameter 
		$ controllerName  =  $ this -> request -> getParam ( 'controller' );
		// Trước 3.4.0 
		$ controllerName  =  $ this -> request -> param ( 'controller' );
		Một số tham số quan trọng mà CakePHP sử dụng nội bộ
			- plugin Plugin xử lý yêu cầu
			- Controller Bộ điều khiển xử lý hiện tại
			- action Hành động xử lý yêu cầu hiện tại
			- prefix tiền tố cho hành động hiện tại
	1.2 Tham số chuỗi truy vấn 
		getQuery($name);
			// URL is /posts/index?page=1&sort=title
				$page = $this->request->getQuery('page');
				// Prior to 3.4.0
				$page = $this->request->query('page');
			trả về null nếu không có 
			// có thể set giá trị mặc định bằng cách
		$this->request->getQuery($name,'default_value');
		// lấy hết toàn bộ các biến 
			$this->request->getQueryParams()
	1.3 Request Body Data (POST);
		Tất cả dữ liệu post có thể được truy cập bằng cách sử dụng
		getData($name, $default = null);
		// tên của thuộc tính  'MyModel[title]' được truy cập
		$title = $this->request->getData('MyModel.title');
		// với các bản trước ;   getData => data('name');
		// nếu không tồn tại sẽ trả về null;
	1.4 PUT, PATCH OR DELETE data
		Tổng quan về các Verb
		PUT: Cập nhật dữ liệu 
		DELETE : Xóa dữ liệu.
		* GET PUT DELETE là các phương thức không thay đổi giá trị tức có 	thể gọi nhiều lần và không gây lỗi cho ứng dụng 
		* POST : tạo mới là phương thức làm thay đổi giá trị, tức là nếu gọi post nhiều lần sẽ tạo ra nhiều dữ liệu giống nhau

		input($ callback[,$tuychon])
		ví dụ: $jsonData = $this->request->input('json_decode');
	1.5. Environment Variables(from $_SERVER AND $_ENV)
		// Lấy host 
		$ host  =  $ this -> request -> env ( 'HTTP_HOST' );

		// Set a value, generally helpful in testing. 
		$ this -> request -> env ( 'REQUEST_METHOD' ,  'POST' );
		lấy tất cả các biến môi trường 
		$env = $this->request->getServerParams(); \\ chỉ hoạt động từ 3.4.0
	1.6 XML or JSON data
		// Get JSON encoded data submitted to a PUT/POST action
		$jsonData = $this->request->input('json_decode');
		// Get XML encoded data submitted to a PUT/POST action
		$data = $this->request->input('Cake\Utility\Xml::build', ['return' => 'domdocument']);
	1.7 Thông tin đường dẫn 
		// Assume the current request URL is /subdir/articles/edit/1?page=1
		// Holds /subdir/articles/edit/1?page=1
		$here = $request->here();
		// Holds /subdir
		$base = $request->getAttribute('base');
		// Holds /subdir/
		$base = $request->getAttribute('base');
		// Prior to 3.4.0
		$webroot = $request->webroot;
		$base = $request->base;
	1.8 Kiểm tra điều kiện yêu cầu 
		Cake\Http\ServerRequest::is($type, $args...)
		$this->request->is('post');

		Cake\Http\ServerRequest::addDetector($name, $options)
			// Add an environment detector.
			$this->request->addDetector(
			    'post',
			    ['env' => 'REQUEST_METHOD', 'value' => 'POST']
			);

			// Add a pattern value detector.
			$this->request->addDetector(
			    'iphone',
			    ['env' => 'HTTP_USER_AGENT', 'pattern' => '/iPhone/i']
			);

			// Add an option detector
			$this->request->addDetector('internalIp', [
			    'env' => 'CLIENT_IP',
			    'options' => ['192.168.0.101', '192.168.0.100']
			]);

			// Add a callback detector. Must be a valid callable.
			$this->request->addDetector(
			    'awesome',
			    function ($request) {
			        return $request->getParam('awesome');
			    }
			);

			// Add a detector that uses additional arguments. As of 3.3.0
			$this->request->addDetector(
			    'controller',
			    function ($request, $name) {
			        return $request->getParam('controller') === $name;
			    }
			);
		Requestcũng bao gồm các phương pháp như Cake\Http\ServerRequest::domain(), Cake\Http\ServerRequest::subdomains()và Cake\Http\ServerRequest::host()để giúp các ứng dụng với các tên miền phụ
			is('get') Kiểm tra xem liệu yêu cầu hiện tại là một GET.
			is('put') Kiểm tra xem liệu yêu cầu hiện tại là một PUT.
			is('patch') Kiểm tra xem yêu cầu hiện tại có phải là PATCH hay không.
			is('post') Kiểm tra xem yêu cầu hiện tại có phải là POST không.
			is('delete') Kiểm tra xem yêu cầu hiện tại có phải là DELETE hay không.
			is('head') Kiểm tra xem yêu cầu hiện tại là HEAD.
			is('options') Kiểm tra xem liệu yêu cầu hiện tại là OPTIONS.
			is('ajax') Kiểm tra xem liệu yêu cầu hiện tại có đến với X-Yêu cầu-Với = XMLHttpRequest.
			is('ssl') Kiểm tra xem yêu cầu có thông qua SSL hay không.
			is('flash') Kiểm tra xem liệu yêu cầu có User-Agent của Flash.
			is('requested') Kiểm tra xem liệu yêu cầu có một tham số truy vấn 'được yêu cầu' với giá trị 1 hay không.
			is('json') Kiểm tra xem yêu cầu có phần mở rộng 'json' và chấp nhận mimetype 'application / json'.
			is('xml') Kiểm tra xem yêu cầu có 'xml' extension và chấp nhận mimetype 'application / xml' hoặc 'text / xml'.
		Trong phiên bản 3.3.0
	1.9. Session Data
			 $ this -> request -> session () -> read ( 'Auth.User.name' ); ???
	1.10. Host and DomainName
		/ Prints 'example.org'
		echo $request->domain();
		// Returns ['my', 'dev'] for 'my.dev.example.org'
		$subdomains = $request->subdomains();
		// Prints 'my.dev.example.org'
		echo $request->host();
	1.11 Reading method
		// Output POST
		echo $request->getMethod();

		// Prior to 3.4.0
		echo $request->method();
	1.12. Restricting Which HTTP method an Action Accepts 
		Hạn chế hàm chỉ chạy với thương thức nào
		public function delete()
		{
		    // Only accept POST and DELETE requests
		    $this->request->allowMethod(['post', 'delete']);
		    ...
		}
	1.13 Đọc tiêu đề HTTP Headers
		// Get the header as a string
		$userAgent = $this->request->getHeaderLine('User-Agent');
		// Get an array of all values.
		$acceptHeader = $this->request->getHeader('Accept');
		// Check if a header exists
		$hasAcceptHeader = $this->request->hasHeader('Accept');
		// Prior to 3.4.0
		$userAgent = $this->request->header('User-Agent');
	1.14 Trusting Proxy Headers
	Nếu ứng dụng chạy sau cần bằng tải hoặc chạy trên dịch vụ đám mây 
		this->request->trustProxy = true;
		// These methods will now use the proxied headers.
		$port = $this->request->port();
		$host = $this->request->host();
		$scheme = $this->request->scheme();
		$clientIp = $this->request->clientIp();
	1.15. Kiểm tra chấp nhận Headers
		Cake\Http\ServerRequest::accepts($type = null)
		$acceptsJson = $this->request->accepts('application/json');
		chấp nhận tất cả các kiểu 
			$accepts = $this->request->accepts();
		Get list accepted language
			$acceptsLanguages = $this->request->acceptLanguage($language = null);
	1.16. Cookies
		// Get the cookie value, or null if the cookie is missing.
		$rememberMe = $this->request->getCookie('remember_me');
		// Read the value, or get the default of 0
		$rememberMe = $this->request->getCookie('remember_me', 0);
		// Get all cookies as an hash
		$cookies = $this->request->getCookieParams();
		// Get a CookieCollection instance (starting with 3.5.0)
		$cookies = $this->request->getCookieCollection()
2. Response 
	Cake\Http\Response
	2.1 Kiểm soát các loại nội dung 
		Bạn có thể kiếm soát ứng dụng với content-type: 
		// Thêm một loại vCard 
		$ this -> response -> type ([ 'vcf'  =>  'text / v-card' ]);
		// Đặt đáp ứng Content-Type thành vcard. 
		$ this -> response  =  $ this -> response -> withType ( 'vcf' );
		// Trước 3,4.0 
		$ this -> response -> type ( 'vcf');
	2.2. Gửi tập tin 
		Cake\Http\Response::withFile($path, $options = [])
		public function sendFile($id)
		{
		    $file = $this->Attachments->getFile($id);
		    $response = $this->response->withFile($file['path']);
		    // Return the response to prevent controller from trying to render
		    // a view.
		    return $response;
		}

		// Prior to 3.4.0
		$file = $this->Attachments->getFile($id);
		$this->response->file($file['path']);
		// Return the response to prevent controller from trying to render
		// a view.
		return $this->response;
	2.3 Gửi một chuối dưới dạng file
		Bạn cso thể trả về 1 file không có trên đĩa dưới dạng pdf hoặc tên tim tạo ta từ 1 chuỗi 
		public function sendIcs()
		{
		    $icsString = $this->Calendars->generateIcs();
		    $response = $this->response;
		    $response->body($icsString);

		    $response = $response->withType('ics');

		    // Optionally force file download
		    $response = $response->withDownload('filename_for_download.ics');

		    // Return response object to prevent controller from trying to render
		    // a view.
		    return $response;
		}

		in 2x

		public function sendIcs() {
		    $icsString = $this->Calendar->generateIcs();
		    $this->response->body($icsString);
		    $this->response->type('ics');

		    //Optionally force file download
		    $this->response->download('filename_for_download.ics');

		    // Return response object to prevent controller from trying to render
		    // a view
		    return $this->response;
		}
	2.4. Setting Header
		in 2x
		// Set a single header
		$this->response->header('Location', 'http://example.com');

		// Set multiple headers
		$this->response->header(array(
		    'Location' => 'http://example.com',
		    'X-Extra' => 'My header'
		));

		$this->response->header(array(
		    'WWW-Authenticate: Negotiate',
		    'Content-type: application/pdf'
		));

		in 3x 
		// Add/replace a header
		$response = $response->withHeader('X-Extra', 'My header');

		// Set multiple headers
		$response = $response->withHeader('X-Extra', 'My header')
		    ->withHeader('Location', 'http://example.com');

		// Append a value to an existing header
		$response = $response->withAddedHeader('Set-Cookie', 'remember_me=1');

		// Prior to 3.4.0 - Set a header
		$this->response->header('Location', 'http://example.com');
	2.5 Setting The Body
		// Set a string into the body
		$response = $response->withStringBody('My Body');

		// If you want a json response
		$response = $response->withType('application/json')
		    ->withStringBody(json_encode(['Foo' => 'bar']));

		    tìm hiểu thêm response tại 
		    	https://book.cakephp.org/2.0/en/controllers/request-response.html 
		    	https://book.cakephp.org/3.0/en/controllers/request-response.html#put-patch-or-delete-data

	CakeResponse cung cấp một số phương pháp hữu ích để tương tác với phản hồi mà bạn gửi cho khách hàng.

	CakeResponse::header( $ header = null , $ value = null )
		Cho phép bạn trực tiếp đặt một hoặc nhiều tiêu đề được gửi kèm theo phản hồi.

	CakeResponse::location( $ url = null )
		Cho phép bạn trực tiếp đặt tiêu đề vị trí chuyển hướng được gửi cùng với câu trả lời:

	// Đặt vị trí chuyển hướng 
	$ this -> response -> location ( 'http://example.com' );

	// Lấy tiêu đề vị trí chuyển hướng hiện tại 
	$ location  =  $ this -> response -> location ();
		Mới trong phiên bản 2.4.
	CakeResponse::charset( $ charset = null )
		Đặt bộ ký tự sẽ được sử dụng trong câu trả lời.

	CakeResponse::type( $ contentType = null )
		Đặt loại nội dung phản hồi. Bạn có thể sử dụng bí danh loại nội dung đã biết hoặc tên loại nội dung đầy đủ.

	CakeResponse::cache( $ kể từ , $ time = '+1 day' )
		Cho phép bạn đặt tiêu đề bộ nhớ cache trong phản hồi.

	CakeResponse::disableCache( )
		Đặt tiêu đề để vô hiệu hóa bộ nhớ đệm của khách hàng để đáp ứng.

	CakeResponse::sharable( $ public = null , $ time = null )
		Thiết lập Cache-Controltiêu đề là một trong hai publichoặc privatevà tùy chọn thiết lập một max-agechỉ thị của tài nguyên

	Mới trong phiên bản 2.1.
	CakeResponse::expires( $ thời gian = null )
		Cho phép đặt Expirestiêu đề vào một ngày cụ thể.

	Mới trong phiên bản 2.1.
	CakeResponse::etag( $ tag = null , $ weak = false )
		Đặt Etagtiêu đề để nhận dạng duy nhất một tài nguyên phản hồi.

	Mới trong phiên bản 2.1.
	CakeResponse::modified( $ thời gian = null )
		Đặt Last-Modifiedtiêu đề cho một ngày tháng cụ thể và đúng định dạng.

	Mới trong phiên bản 2.1.
	CakeResponse::checkNotModified( Yêu cầu CakeRequest $ )
		So sánh tiêu đề bộ nhớ cache cho đối tượng yêu cầu với tiêu đề bộ nhớ cache từ phản hồi và xác định xem nó có thể vẫn được xem là tươi. Nếu có, xóa nội dung phản hồi và gửi tiêu đề 304 Not Modified .

	Mới trong phiên bản 2.1.
	CakeResponse::compress( )
		Bật nén gzip theo yêu cầu.

	CakeResponse::download( $ tên tập tin )
		Cho phép bạn gửi phản hồi dưới dạng tập tin đính kèm, và để đặt tên tập tin.

	CakeResponse::statusCode( $ code = null )
		Cho phép bạn thiết lập mã trạng thái của câu trả lời.

	CakeResponse::body( $ content = null )
		Thiết lập nội dung của phản hồi.

	CakeResponse::send( )¶
		Một khi bạn đã hoàn thành tạo ra một phản ứng, cuộc gọi send()sẽ gửi 	tất cả các tiêu đề thiết lập cũng như cơ thể. Điều này được thực hiện tự động vào cuối mỗi yêu cầu của Dispatcher.

	CakeResponse::file( $ path , $ options = array () )
		Cho phép bạn đặt Content-Dispositiontiêu đề của một tệp để hiển thị hoặc để tải về.