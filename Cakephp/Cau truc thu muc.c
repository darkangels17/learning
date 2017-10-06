1. Cấu trúc thư mục của CakePhP
	* bin  chứa các file thực thi của Cake Console
	* config chứa các tập tin cấu hình: cơ sở dữ liệu, bootstrapping ... 
	* logs các file ghi logs tùy theo cấu hình của mình
	* plugins chứa các plugins đang sử dựng 
	* src 
		* Console hỗ trợ sinh code thông qua command line
		* Controler chứa Controller và component
		* Model chưa file Model và behavor, datasourse
		* Shell
		* Template
		* View thư mục chứa file giao diện 
	* Tests thư mục thử nghiệm cho các trường hợp thử nghiệm 
	* Tmp thư mục tạm của ứng dụng 
	* vendor chứa ứng dụng của bên thứ 3 
	* webroot chứa tài liệu hình ảnh, file css, file javascript
2. 	Cấu hình chung 
	* debug Thay đổi CakePhP debugging output 
		false: không đưa ra thông báo lỗi, cảnh báo
		true: thông báo lỗi và cảnh báo được đưa ra 
	* App.namespace 
		các tên để tìm các ứng dụng bên dưới
	* App.baseUrl
		??????????????
	* App.base 
	* App.encoding
	* App.webroot thư mục webroot
	* App.wwwRoot  đường dẫn tới tập webroot
	* App.fullBaseUrl: Tên miền đầy đủ (bao gồm cả giao thức) vào root ứng dụng của bạn 
	* App.imageBaseUrl: Đường dẫn Web tới thư mục hình ảnh công cộng dưới webroot
	* App.cssBaseUrl: 
	* App.jsBaseUrl: 
	* App.paths định cấu hình đường dẫn cho các tài nguyên không dựa trên lớp . Hỗ trợ plugins, templates, locales subkeys ..
	* Security.salt : một chuỗi ngẫu nhiên sử dụng cho hàm băm
	* Asset.timestamp: gắn thêm dấu thời gian sửa đổi cuối cùng của tệp cụ thể 
		- false không làm gì 
		- true Nối thêm thời gian khi gỡ lỗi là đúng 
		- force luôn luôn gắn dấu thời gian 
3. Cấu hình cơ sở dữ liệu 
	Cơ sở dữ liệu có thể cấu hình tại file config/app.php 
		'className' => 'Cake\Database\Connection';
		'driver' => '' driver kết nối vs các hệ quản trị cơ sở dữ liệu 
		'persistent' => false // có hay không sử dụng kết nối liên tục tới cơ sở dữ liệu
		'host' => '' địa chỉ của Database
		'userName' => 'tên đăng nhập Database'
		'password'
		'port' => '3306'
		'Database' => 'tên Database'
		'encoding' => 'utf8'
		'timezone' => 'UTC' mã thời gian 
		'flags' => []
		......
		'int' một danh sách các câu