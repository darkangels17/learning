															=======================================================
															 	================================================			
																	 _____ _____ _____    _____         _     
																	|  _  |  |  |  _  |  | __  |___ ___|_|___ 
																	|   __|     |   __|  | __ -| .'|_ -| |  _|
																	|__|  |__|__|__|     |_____|__,|___|_|___|
								                                  
																================================================	
															=======================================================				                   
										1. Introduction
											php hỗ trợ 10 kiểu 
												* Boolean, integer, float string
												* array, object, callable, iterable
												* resource, NULL
										1.1. Boolean
											* Chuyển kiểu vể Boolean
												(bool) $tên_biến;
												integer 0 => false;
												float 0.0 => false;
												String "" or "0" => false;
												array with zero elements => false;
												kiểu NULL => false;
												Simple Xml object emptytags
										1.2. integer
											$a = 1234 // hệ 10
											$a = 0123 -> 07123 hệ 8   086 => lỗi (không tự convert)
											$a = 0x34 -> hệ cơ số 16 
											$a = 0b1101 -> hệ nhị phân 
											Convert to String 
											Boolean true -> 1, false = 0;
											(int) "1.2.1fdasasd" -> 1;
											1+"10.5" = 11.5
											12+"1sffd" = 13;
											(int) ((0.1+0.7)*10)  ==> kết quả bất ngờ 7
											(int) ((0.1+0.8)*10)  ==> kết quả là 9
										1.3 Float point numbers
										1.4 String
											'this is string' or "this is tring"
											'this \n daa' => this /n daa
											"this \n ddd" => this
															 ddd
											Dùng ngoặc đơn sẽ escaping các kí tự đặc biệt
											In biến trong chuỗi nên dùng trong {}
										1.5 Array 
											$array array (
												key => value,
												key2 => value,
											)
											Eg1. 
											<?php
											$array = array(
											         "a",
											         "b",
											    6 => "c",
											         "d",
											);
											var_dump($array);
											?> 
											result 
											array(4) {
											[0]=>
											string(1) "a"
											[1]=>
											string(1) "b"
											[6]=>
											string(1) "c"
											[7]=>
											string(1) "d"
											}
											Eg2. $a = array(
											1 => 'a',
											true => "b";
											) vị trí 1 sẽ bị ghi đè giá trị mảng có 1 phần tử 

											$arr = array(5=>1, 12 =>2);
											$arr[] = 16; => $arr[13] = 16;
											unset($arr[13]); delete p tử thứ 13
											unset($arr); delete array
											foreach($arr as $key => $value) {
											// doing 
											}
										1.6 Iterable
											ý hiểu: Chấp nhận bất kì mảng hoặc đối tượng thực hiện giao diện 
											Traversable 
												Eg1.
												function foo(iterable $iterable) {
												    foreach ($iterable as $value) {
												        // ...
												    } 
												}

												function bar(): iterable {
												    return [1, 2, 3];
												}

												function gen(): iterable {
												    yield 1;
												    yield 2;
												    yield 3;
												}
										1.7 Object 
												class foo
												{
												    function do_foo()
												    {
												        echo "Doing foo."; 
												    }
												}
												$bar = new foo;
												$bar->do_foo();
											Eg2 Convert to object
												<?php
												$obj = (object) 'ciao';
												echo $obj->scalar;  // outputs 'ciao'
												?> 
										1.8. Resources
											Là một biến đặc biệt, chứa một tham chiếu đến một resource bên ngoài. Các resource được tạo ra và sử dụng bởi các
										hàm đặc biệt.Giải phóng resources: bởi do tham chiếu đếm của hệ thống được giới thiệu trong PHP4 Zend-engine, nó sẽ tự
										động phát hiện khi một resource không cần thiết cho lâu dài. Khi ở trong trường hợp này, tất cả các resource mà đã được
										dùng cho resource này được giải phóng bởi “bộ phận thu nhặt rác”. Do đó, hiếm khi thật sự cần thiết để giải phóng bộ 
										nhớ thông thường bằng cách sử dụng hàm free_result().
										1.9 NULL
											Là một giá trị đặc biệt thể hiện 1 biến không có giá trị:  
											is_null(), unset()
										1.10. Callbacks/Callables
											* is_callable: kiểm tra biến được truyền vào có phải là một hàm không ;
											* Là khái niệm một hàm được truyền vào một hàm khác như một tham số để có thể thực hiện trước hoặc sau một sự kiện
											hoặc một sự thay đổi trạng thái 
											Eg1.
												<?php
												function sayHello($callback) {
												    echo "Xin chào!</br>";
												    // Các câu chuyện khác ở giữa xin chào và tạm biệt
												    // ...
												    $callback();
												}
												function sayGoodbye() {
												    echo "Tạm biệt!";
												}

												sayHello('sayGoodbye');
												// Kết quả
												// Xin chào!
												// ...
												// Tạm biệt
											Eg2
												<?php
												function sayHello($first_name, $last_name, $callback) {
												    $full_name = $first_name . ' ' . $last_name;
												    $callback($full_name);
												}
												function formatName($full_name) {
												    echo '<h2 style="color:red;">Xin chào '. $full_name . '!<h2>';
												}

												sayHello('Nguyễn Văn', 'A', 'formatName');

											Ví dụ về lập xử lý đa luồng, chúng ta cần mở một file và ghi vào file một cái gì đó, vì file này rất lớn nên 
											việc mở file có thể mất một chút thời gian. Nếu như viết theo cách cũ:
												fileObject = open(file)
												// Cần phải chờ file được mở thì mới ghi vào file được, có thể mất 5 phút chẳng hạn.
												fileObject.write("We are writing to the file.")
												// Tiếp theo mới làm được những việc khác
												doSomething();
												Sử dụng callback, chúng ta có thể thực hiện được những việc khác luôn
												fileObject = open(file, writeToFile)
												// Không cần phải chờ file mở và ghi vào file, chúng ta có thể thực hiện việc khác luôn.
												doSomething();
										1.11. Pseudo-types and variables
											a. mix : là tham số hỗn hợp chấp nhận nhiều kiểu dữ liệu tuy nhiên không phỉa là tất cả
											b. number : chỉ ra các tham số có thể là kiểu integer hoặc float
											c. callback: 
											d. array|object chỉ ra là tham số có thể là kiểu array hoặc object
											e. void: 
										1.12. Type Juggling
											(int) cast to int ...
											.....
											(binary) $string or b"adđs"
											(unset) cast to NULL (PHP5);
															=======================================================
															 	================================================			
																	 _____ _____ _____    _____         _     
																	|  _  |  |  |  _  |  | __  |___ ___|_|___ 
																	|   __|     |   __|  | __ -| .'|_ -| |  _|
																	|__|  |__|__|__|     |_____|__,|___|_|___|
								                                  
																================================================	
															=======================================================	