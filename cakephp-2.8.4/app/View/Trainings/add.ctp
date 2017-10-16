<div>
	<lable>管理システム</label>
	<?php echo $this->Form->create('Training'); ?>
		<?php if(isset($error)) { ?>
		<div class = 'err'>
			<?=$error ?>
		</div>
		<?php } ?>
		
		<table>
			<tr>
				<td> User Name </td>
				<td><?php echo $this->Form->input('userName',['label'=>false]);?></td>
			</tr>
			<tr>
				<td> Email </td>
				<td><?php echo $this->Form->input('email',['label'=>false]);?></td>
			</tr>
			<tr>
				<td> Password </td>
				<td><?php echo $this->Form->input('password',['label'=>false]);?></td>
			</tr>
			<tr>
				<td> Confirm Password </td>
				<td><?php echo $this->Form->input('confirmPassword',['type'=>'password','label'=>false]);?></td>
			</tr>
			<tr>
				<td> Address </td>
				<td><?php echo $this->Form->input('address',['label'=>false]);?></td>
			</tr>
			<tr>
				<td> Birthday </td>
				<td><?php echo $this->Form->input('birthday',['type'=>'text','label'=>false]);?></td>
			</tr>
			<tr>
					<td> Member Type </td>
					<td><?php
 						echo $this->Form->input('type', [
 							'options' => ['0'=>'User','1'=>'Admin'],
 							'default' => '0',
 							'type' =>'radio',
 							]);
						?>
					</td>
			</tr>
			</tr>
				<td><center><?php  echo $this->Form->end('Add');?></center></td>
				<td><input type = 'button' value= 'Back' onclick = "location.href = 'index'"/></td>
			</tr>
		</table>
	
</div>