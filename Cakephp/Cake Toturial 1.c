						========================================================================================================
							                    ==============================================================
									   ______      __           ____  __  ______     ______      __             _       __
									  / ____/___ _/ /_____     / __ \/ / / / __ \   /_  __/___  / /___  _______(_)___ _/ /
									 / /   / __ `/ //_/ _ \   / /_/ / /_/ / /_/ /    / / / __ \/ __/ / / / ___/ / __ `/ / 
									/ /___/ /_/ / ,< /  __/  / ____/ __  / ____/    / / / /_/ / /_/ /_/ / /  / / /_/ / /  
									\____/\__,_/_/|_|\___/  /_/   /_/ /_/_/        /_/  \____/\__/\__,_/_/  /_/\__,_/_/ 
												===============================================================
						======================================================================================================== 
									                                                                                     
						1. Cấu trúc thư mục của CakePhP
							* App thư mục chứa tất cả mã nguồn
								* Config chứa các tập tin cấu hình: cơ sở dữ liệu, bootstrapping ... 
								* Console hỗ trợ sinh code thông qua command line
								* Controler chứa Controller
									* Component: Component là những thành phần mở rộng trong CakePHP, cho phép
									 người sử dụng một cách linh hoạt và có thể tùy biến lại. Trong Cakephp có 
									 hỗ trợ một số component mà ta thường dùng là: ACL, mail, time…. chúng được 
									 sử dụng trong controller. Ngoài ra chúng ta cũng có thể viết một component 
									 của riêng mình để sử dụng
								* Model: chứa file Model và behavor, datasource
								* lib chứa thư viện 
								* Locale: Chứa file ngôn ngữ, sử dụng cho ứng dụng đa ngôn ngữ 
								* Plugins chứa các plugins đang sử dựng 
								* Tests thư mục thử nghiệm cho các trường hợp thử nghiệm 
								* Tmp thư mục tạm của ứng dụng
									* cache
									* logs
									* sesions
									* tests
								* Vendor: chưa thư mục của bên thứ 3 giống như thư mục vendors bên ngoài 
								* View chứa các giao diện hiển thị và 
									* Helper: là tập hợp các thư viện, công thức,… để có thể sử dụng bất cứ đâu 
									 trong view. Cakephp hỗ trợ sẳn các helper như: form, html, ajax, number, session…
									 Cũng như compoment ta cũng có thể viết helper cho riêng mình
								* webroot chứa các tập tin tài liệu hình ảnh, javascript,css
							* plugins : chứa các thành phần mở rộng của ứng dụng 
							* libs : chứa file thư viện 
							* vendors: ứng dụng của bên thứ 3
						2. Quy ước đạt tên trong CakePHP
							2.1 Tên file, tên class
								- Tên file sử dụng chữ thường, viết hoa chữ cái phân tách các từ
								- Tên class viết hoa chữ cái đầu tiên của từ 
							2.2 Quy ước về cơ sở dữ liệu mà Model
								- Tên class trong Model phải ở dạng số ít và viết hoa chữ cái đầu của các từ
								- Tên các bảng trong database phải là số nhiều.
								- CakePHP không hỗ trợ khóa chính gồm nhiều cột. Nếu muốn kết nối join các bảng hãy truy vấn
								trực tiếp hoặc thêm một khóa chính thay cho khóa nhiều cột
								- Khóa chính mặc định trong CakePHP là cột id tự tăng. Tuy nhiên có thể định nghĩa lại khóa 
								chính thông qua biến $primaryKey trong Model.
								- Các khóa ngoại trong quan hệ có tên mặc định là số ít của tên bảng kèm theo +"_id" ở cuối
							2.3 Quy ước về controller
								- tên lớp của controller phải là số nhiều và thêm "Controller" ở cuối cùng
							2.4 Quy ước về View
								Trong View chia làm hai cấp dộ thư mục và file 
									- Tên thư mục phải tương ứng với controller
									- Tên file của View phải tương ứng với các phương thức trong controller
									- Đuôi mở rộng của các file reong view là ".ctp"
									EG1
										Ví dụ : giả sử trong database ta có một bảng tên categories ta sẽ có các Model, Controller, View như sau
										– Model: sẽ có file Category.php
										– Controller: sẽ có file CategoriesController.php
										– View: sẽ có thư mục Categories
										– Thêm 2 phương thức vào trong CategoriesController.php nội dung như sau:
										<?php
										class CategoriesController extends AppController{
										   public function menu(){
										 
										   }
										   public function index(){
										 
										   }
										}
										?>
						3. 	Cấu hình chung 
							3.1 Debug chấp nhận các giá trị 0,1,2 
								0: không đưa ra thông báo lỗi, cảnh báo
								1: thông báo lỗi và cảnh báo được đưa ra 
								2: Hiển thị lỗi, cảnh bảo và các câu truy vấn sql được đưa ra 
									'Từ phiên bản 1.3.x, câu truy vấn sql chỉ hiện ra khi trong layout chúng ta thêm đoạn code sau:
													<?php echo $this->element('sql_dump'); ?>'
							3.2 log 
								- Lưu lỗi, cảnh báo vào file log
								- chấp nhận hai giá trị true, false
									true: cho log
									false: không log
							3.3 App.baseUrl (*)
								- Bỏ dấu chú thích cho dòng này nếu bạn không muốn dùng mod_rewrite của Apache. Nếu làm điều này, 
								bạn đừng quên xóa bỏ các file .htaccess trong app, app/webroot và thư mục ngoài cùng (trên app một nấc)

							3.4 Routing.prefixes (Routing.admin)
								- Cho phép thiết dẫn một đường dẫn vào một khu vực ảo nào đó. 
								- Giả sử ta cấu hình để truy xuất vào khu vực quản trị nội dung:
									Configure::write('Routing.prefixes', array('admin'));
									Nghĩa là khi gõ http://localhost/cakephp1.3.2/admin 
									//thì CakePHP sẽ hiểu ta muốn tới khu vực admin, 
									//tuy nhiêntrên ứng dụng chúng ta không hề có thư mục nào tên là admin cả, 
									//thay vào đó, các phương thức trong controller sẽ phải gắn thêm tiền tố admin_.
								Eg1: Ví dụ: trong controller NewsController, ta có phương thức thêm mới bản tin
								và ta muốn nó chỉ được truy xuất trong khu vực admin, muốn như thế thì 
								tên phương thức này phải có dạng như sau:
									function admin_add() {
									}
							3.5 Cache.disable
								- Bật chức năng catching
									Configure::write('Cache.disable', true); or false;
							3.6 Session.save
								- Các kiểu lưu session…
								- Các giá trị:
								php: dùng các thiết lập trong file php.ini
								cake: lưu session vào file trong thư mục app/tmp 
								database: lưu session vào csdl. Muốn dùng bạn phải chạy lệnh "cake schema run create Session"
								trong Console (*sẽ tiếp tục tìm hiểu sau*)
							3.7 Session.timeout
								- thiết lập thời gian lưu trữ session đơn vị tính bắng 'second' dùng kết hợp vs Security.level
							3.8 Session.start
								- Tự động start session : true or false
							3.9 Security.level 
								- Các mức độ bảo mật: hight, medium, low
									hight: session timeout = Session.timeout*10;
									medium: session timeout = Session.timeout*5040;
									low: session timeout = Session.timeout*2628000;
							3.10 Security.salt
								- chuỗi ngẫu nhiên cho hàm băm
							3.11 Security.cipherSeed
								- chuỗi ngẫu nhiên dùng để mã hóa / giải mã chuỗi
							* App.namespace các tên để tìm các ứng dụng bên dưới
							* App.base 
							* App.encoding
							* App.webroot thư mục webroot
							* App.wwwRoot  đường dẫn tới tập webroot
							* App.fullBaseUrl: Tên miền đầy đủ (bao gồm cả giao thức) vào root ứng dụng của bạn 
							* App.imageBaseUrl: Đường dẫn Web tới thư mục hình ảnh công cộng dưới webroot (sử dụng khi không sử dụng defaut)
							* App.cssBaseUrl: 
							* App.jsBaseUrl: 
							* App.paths định cấu hình đường dẫn cho các tài nguyên không dựa trên lớp . Hỗ trợ plugins, templates, locales subkeys ..
							* Asset.timestamp: gắn thêm dấu thời gian sửa đổi cuối cùng của tệp cụ thể 
								- false không làm gì 
								- true Nối thêm thời gian khi gỡ lỗi là đúng 
								- force luôn luôn gắn dấu thời gian 

						4 Cấu hình cơ sở dữ liệu 
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
						========================================================================================================
							                    ==============================================================
									   ______      __           ____  __  ______     ______      __             _       __
									  / ____/___ _/ /_____     / __ \/ / / / __ \   /_  __/___  / /___  _______(_)___ _/ /
									 / /   / __ `/ //_/ _ \   / /_/ / /_/ / /_/ /    / / / __ \/ __/ / / / ___/ / __ `/ / 
									/ /___/ /_/ / ,< /  __/  / ____/ __  / ____/    / / / /_/ / /_/ /_/ / /  / / /_/ / /  
									\____/\__,_/_/|_|\___/  /_/   /_/ /_/_/        /_/  \____/\__/\__,_/_/  /_/\__,_/_/ 
												===============================================================
						======================================================================================================== 