<div>
	<div>
		<form method = 'post'>
			<table >
				<tr>
					<th>
						<lablel>Email</label>
					</th>
					<th> 
						<input type = 'text' name = 'Email' > </input> 
					</th> 
					<th>
						<input type="submit" name="Search" value="Search" />
					</th> 
				</tr>
			</table>
		</form>
	</div>
	<div>
		<label><b>Total User</b>: <?=$total?> </label> 
		<table >
			<tr>
				<th>User Id</th>
				<th>User Name</th> 
				<th>Email</th> 
				<th>Birthday</th>
				<th>Address</th>
				<th>Type</th>
				<th>Action</th> 
			</tr>
		 <?php foreach ($listUser as $user) { ?>
			<tr>
				<td><?=$user['Training']['id']?></td>
				<td><?=$user['Training']['userName']?></td>
				<td><?=$user['Training']['email']?></td>
				<td><?php echo date('d-m-Y',strtotime($user['Training']['birthday'])); ?></td>
				<td><?=$user['Training']['address']?></td>
				<?php 
					if($user['Training']['type'] == 1){
				?>
					<td>Admin</td>
					<td><?php echo $this->Html->link('Edit',['controller'=>'Trainings','action'=>'edit','?'=>['id'=>$user['Training']['id']]])?></td>
				<?php }else { ?>
					<td>User</td>
					<td><?php echo $this->Html->link('Edit',['controller'=>'Trainings','action'=>'edit','?'=>['id'=>$user['Training']['id']]])?>|<?php echo $this->Html->link('Delete',['controller'=>'Trainings','action'=>'delete','?'=>['id'=>$user['Training']['id']]])?></td>
				<?php } ?>
			</tr>
		<?php }?>
		</table>
		<?php
		    echo $this->Paginator->prev('« Previous ', null, null, array('class' => 'disabled')); //Hiện thj nút Previous
		    echo " | ".$this->Paginator->numbers()." | "; //Hiển thi các số phân trang
		    echo $this->Paginator->next(' Next »', null, null, array('class' => 'disabled')); //Hiển thị nút next
		    //echo "   Page ".$this->Paginator->counter(); // Hiển thị tổng trang
		?>
		</div>
	<center><?php echo $this->Html->link('ADD',['controller'=>'Trainings','action'=>'add'])?></center>
</div>