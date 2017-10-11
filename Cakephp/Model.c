

1. Models
	Chịu trách nhiệm quản lý hầu hết mọi thứ liên quan đến dữ liệu, tính hợp lệ và tương tác của dữ liệu.
	Thông thường các lớp Model mô tả dữ liệu và được sử dụng trong các ứng dụng CakePHP để truy cập dữ liệu. Chúng đại diện 
	cho một bảng cơ sở dữ liệu nhưng có thể sử dụng để truy cập vào bất cứ dữ liệu tệp ...
1.1 Tổng quát
	Trong lập trình hướng đối tượng, Model là một đối tượng đại diện cho một vật như xe hơi ....
	App::uses('AppModel', 'Model');
	class Ingredient extends AppModel {
	    public $name = 'Ingredient';
	}
	Lớp trung gian AppModel có ý nghĩa giống với lớp trung gian AppController;
chú ý: CakePHP sẽ tự động tạo ra một Model nếu không thể tìm thấy tệp tương ứng 
		Một số tên lớp không được sử dụng cho tên mô hình. ví dụ "File" không thể được sử dụng vì trùng vs một lớp trong lõi
		của CakePHP.
	- 'Khi Model được định nghĩa, nó có thể truy cập trong Controller. CakePHP sẽ tự động làm cho mô hình có sẵn để truy cập Khi
	tên của nó phù hợp với bộ điều khiển' 
	VD: BookController sẽ tự động khởi tạo Model và gắn nó vào Controller 
		$this->Book:
	- 'Các mô hình liên kết có sẵn thông qua mô hình chính'
		class Recipe extends AppModel {
		    public function steakRecipes() {
		        $ingredient = $this->Ingredient->findByName('Steak');
		        return $this->findAllByMainIngredient($ingredient['Ingredient']['id']);
		    }
		}
2. Các loại quan hệ trong CakePHP
	2.1 Quan hệ một - một  hasOne
		Mối quan hệ được thê hiện bằng biến $hasOne 
			giả sử tại 1 thời điểm 1 user chỉ có 1 profile 

			class User extends AppModel {
			    var $name = 'User';
			    var $hasOne = array(
			        'Profile' => array(
			            'className' => 'Profile',
			            'conditions' => array('Profile.published' => '1'),
			            'dependent' => true
			    ));
			}
		className: tên lớp của model có quan hệ với model hiện tại.

		foreignKey: tên của khóa ngoại được tìm thấy ở model có quan hệ với model hiện tại.

		conditions: phần bổ sung để làm rõ hơn quan hệ bằng cách đặt tên Model phía trước tên trường. Vi dụ: ghi là “Profile.approved = 1” thì tốt hơn chỉ ghi “approved = 1.”
					Diều kiện thêm
		fields: Danh sách các trường được trả về khi lấy dữ liệu từ quan hệ được thiết lập, mặc định sẽ trả về tất cả các trường.

		order: thứ tự sắp xếp các dòng được trả về.

		dependent: xác định xem khi xóa dữ liệu từ model hiện tại thì model có quan hệ với model hiện tại có bị xóa hay không.

	2.2 Quan hệ một - nhiểu hasMany
			class User extends AppModel {
			    var $name = 'User';
			    var $hasMany = array(
			        'Post' => array(
			            'className' => 'Post',
			            'foreignKey' => 'user_id',
			            'conditions' => array('Post.published' => '1'),
			            'order' => 'Post.created DESC',
			            'limit' => '5',
			            'dependent'=> true
			    ));
			}

	2.3 Quan hệ nhiều - một belongsTo
			class Profile extends AppModel {
			    var $name = 'Profile';
			    var $belongsTo = array(
			        'User' => array(
			            'className' => 'User',
			            'foreignKey' => 'user_id'
			    ));
			}
			counterCache : Nếu thiết lập đúng, mô hình kết hợp sẽ tự động tăng hoặc giảm trường "[singular_model_name] _count" trong bảng nước ngoài bất cứ khi nào bạn làm một save()hoặc delete(). 
			Nếu đó là một chuỗi, thì đó là tên trường để sử dụng. Giá trị trong trường cập trình đại diện cho số hàng liên quan. Bạn cũng có thể chỉ định nhiều bộ nhớ truy cập bằng cách định nghĩa một mảng. 
			counterScope : Các mảng điều kiện tùy chọn sử dụng để cập nhật trường dữ liệu bộ nhớ cache.
		2.3.1 counterCache 
		Tính năng này giúp bạn lưu trữ dữ liệu liên quan đến bộ nhớ cache. 
		Thay vì đếm các bản ghi theo cách thủ công find('count'), mô hình sẽ theo dõi bất cứ sự
		bổ sung/xóa đối với $hasMany
			Tên trường: tên mô model n + '_count'; image_comment_count; 
			thêm trường này vào Model Image
			class ImageCommnet extends AppModel {
				public $belongsTo = array('Image'=>array(
					'counterCache'=>true;
					)
				)
			}
		2.3.2 counterScope
			Bạn cũng có thể chỉ định counterScope. Nó cho phép bạn chỉ định một điều kiện đơn giản mà nói với các mô hình khi cập nhật
		(hoặc khi không, phụ thuộc vào cách bạn nhìn vào nó) giá trị truy cập.
				class ImageComment extends AppModel {
				    public $belongsTo = array(
				        'Image' => array(
				            'counterCache' => 'active_comment_count', //custom field name
				            // only count if "ImageComment" is active = 1
				            'counterScope' => array(
				              'ImageComment.active' => 1
				            )
				        )
				    );
				}
		2.3.3. Nhiều counterCache
				class Message extends AppModel {
				    public $belongsTo = array(
				        'User' => array(
				            'counterCache' => array(
				                'messages_read' => array('Message.is_read' => 1),
				                'messages_unread' => array('Message.is_read' => 0)
				            )
				        )
				    );
				}
			//  nghiên cứu sâu sau
	2.4 Quan hệ nhiều - nhiều hasAndBelongsToMany;

			class Post extends AppModel {
			    var $name = 'Post';
			    var $hasAndBelongsToMany = array(
			        'Tag' =>array(
			            'className' => 'Tag',
			            'joinTable' => 'posts_tags',
			            'foreignKey' => 'post_id',
			            'associationForeignKey' => 'tag_id',
			            'unique' => true,
			            'conditions' => '',
			            'fields' => '',
			            'order' => '',
			            'limit' => '',
			            'offset' => '',
			    ));
			}
	//Sample results from a $this->Profile->find() call.

		Array
		(
		   [Profile] => Array
		        (
		            [id] => 12
		            [user_id] => 121
		            [skill] => Baking Cakes
		            [created] => 2007-05-01 10:31:01
		        )
		    [User] => Array
		        (
		            [id] => 121
		            [name] => Gwoo the Kungwoo
		            [created] => 2007-05-01 10:31:01
		        )
		)
3. Truy xuất dữ liệu
	Model::find(String $type, array $params = array());
			$type: all: lấy tất cả dữ liệu trả về dạng mảng
			first: lấy dữ liệu đầu tiên
			count: tổng số dũ liệu mà hàm find đến được
			list: trả về một mảnh danh sách đã được index
			neighbors: tương tự với fisrt nhưng két quả trả về dữ liệu trước và sau
			threaded: kết quả trả về là một mảng lồng nhau và thường được dùng để dựng
			một kết quả lồng nhau với parent_id.
		Biến $type có thể tạo ra theo ý mình. Đầu tiên phải khai bóa type cho biến 
			Model::$findMethods
				class Article extends AppModel {
				  public $findMethods = array('available' =>true); 
				  protected function _findAvailable($state, $query, $results = array()) {
				    if ($state === 'before') {
				     $query['conditions']['Article.published'] = true;
				     return $query;
				    }
				    return $results;
				  }
				}
			Trong Controller sẽ gọi như sau 
				class ArticlesController extends AppController {
				   //Will find all published articles and order them by the created column
				   public function index() {
				    $articles = $this->Article->find('available', array(
				       'order' => array('created' => 'desc')
				    ));
				   }
				}
		$params có thể có hoặc không, nó là một mảng 
		array(
	  'conditions' => array('Model.field' => $thisValue), //mảng các điều kiện
	  'recursive' => 1, //kiểu int
	  'fields' => array('Model.field1', 'DISTINCT Model.field2'),//mảng tên các trường được lấy
	  'order' => array('Model.created', 'Model.field3 DESC'),//chuỗi hoặc mảng định nghĩa thứ tự order
	  'group' => array('Model.field'), //mảng các trường sẽ GROUP BY
	  'limit' => n, //kiểu int
	  'page' => n, //kiểu int
	  'offset' => n, //kiểu int
	  'callbacks' => true //có thể là các giá trị khác như: false, 'before', 'after'
		)
		conditions: sẽ chứa một mảng các điều kiện, mặc định là null
		recursive: một kiểu số, mặc định là 1(chi tiết sẽ có một bài riêng).
		fields: mảng các trường được trả về mặc định là null.
		order: nó sẽ sắp xếp dữ liệu tăng dần hoặc giảm dần như query thường, nhận giá trị sẽ là chuỗi hoặc mảng, mặc định null.
		group: mảng các trường được group by, mặc định null.
		limit: giới hạn dữ liệu trả về, mặc định null.
		page: số page được dùng với những dữ liệu phân trang, mặc định null
		offset: giống như query thông thường, mặc định null.
		callbacks: có thể nhận các giá trị true, false, ‘before’ và ‘after’. 
			Mặc định là true, tức là callback method sẽ được gọi khi dùng find(). 
			Nếu set thành false sẽ hủy việc gọi này. 
			Trường hợp dùng ‘before’ sẽ gọi before callback, 
			ngược lại sẽ gọi after callback khi dùng ‘after’
		Sau khi sử dụng find() dữ liệu sẽ trả về có dạng mảng bao gồm cả dữ liệu của model chính
		và model liên kết nếu sử dụng hợp lý recursive
		findAllBy_(): Hàm này sẽ trả về kết quả giống như find(), nhưng nó sẽ find theo các trường được chỉ định, 
		cú pháp: 
				findAllBy<fieldName>(string $value, array $fields, array $order, int $limit, int $page, int $recursive)
				fieldName: là tên trường trong database.
					$this->Product->findAllByOrderStatus('3');
		findBy_(): Hàm này trả về duy nhất một kết quả dữ liệu giống find(‘first’) nhưng nó cũng chỉ định find theo tên một trường nào đó,
		 cú pháp: findBy<fieldName>(string $value[, mixed $fields[, mixed $order]]);
		query(): truy xuất dữ liệu theo kiểu truyền thống  chỉ cần viết câu SQL bình thường và gọi hàm,
		cú pháp: query(string $query);
	Model::field();
	field(string $name, array $conditions = null, string $order = null);
		trả về 1 trường duy nhất, được xác định là name
			$this->Post->id = 22;
			echo $this->Post->field('name'); // echo the name for row id 22
			// echo the name of the last created instance
			echo $this->Post->field(
			    'name',
			    array('created <' => date('Y-m-d H:i:s')),
			    'created DESC'
			);
	Model::read()
	read($fields,$id);
	luôn trả về một mảng. 
	$fields tên trường cần lấy
	$id chỉ định địa chỉ id sẽ được đọc. được chỉ định bởi Model::$id;
Nhiều điều kiện tìm kiếm 
	$ conditions  =  array ( "Post.title"  =>  "Đây là bài đăng" ,  "Post.author_id"  =>  1 ); 
	// Sử dụng ví dụ với mô hình: 
	$ this -> Post -> find ( 'first' ,  array ( 'conditions'  =>  $ conditions ))

	array("Post.title !=" => "This is a post") // khác vói

	// In
	array(
    "Post.title" => array("First post", "Second post", "Third post")
	)
	//Not in
	array(
	    "NOT" => array(
	        "Post.title" => array("First post", "Second post", "Third post")
	    )
    )
    // in and create > ??
    array (
    "Post.title" => array("First post", "Second post", "Third post"),
    "Post.created >" => date('Y-m-d', strtotime("-2 weeks"))
	)
    // compare 
    array("Post.created = Post.modified")
    ....... https://book.cakephp.org/2.0/en/models/retrieving-your-data.html