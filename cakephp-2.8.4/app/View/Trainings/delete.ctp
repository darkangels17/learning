<?php echo $this->Form->create('Delete', array(
    'onsubmit' => "return confirm(\"Bạn có muốn xóa người dùng này\");"
    ));?>
<div>
	<lable><a>管理システム</a></label>
	<?php echo $this->Form->create('Training'); ?>
		<?php if(isset($error)) { ?>
		<div class = 'err'>
			<?=$error ?>
		</div>
		<?php } ?>
		<?php if(isset($user)) {?>
			<table>
				<tr>
					<?php echo $this->Form->input('id',['type'=>'hidden','label'=>false,'value'=>$user['Training']['id']]);?>
					<td> User Name </td>
					<td><?php echo $this->Form->input('userName',['readonly'=> True,'label'=>false,'value'=>$user['Training']['userName']]);?></td>
				</tr>
				<tr>
					<td> Email </td>
					<td><?php echo $this->Form->input('emailEdit',['readonly'=> True,'label'=>false,'value'=>$user['Training']['email']]);?></td>
				</tr>
				<tr>
					<td> Address </td>
					<td><?php echo $this->Form->input('address',['readonly'=> True,'label'=>false,'value'=>$user['Training']['userName']]);?></td>
				</tr>
				<tr>
					<td> Birthday </td>
					<td><?php echo $this->Form->input('birthday',['readonly'=> True,'type'=>'text','label'=>false,'value'=>$user['Training']['birthday']]);?></td>
				</tr>
				<tr>
					<td> Member Type </td>
					<td> 
					<?php 
					   if($user['Training']['type'] == 0){
				   				echo $this->Form->input('type',['readonly'=> True,'type'=>'text','label'=>false,'value'=>'User']);
				   			} else {
				   				echo $this->Form->input('type',['readonly'=> True,'type'=>'text','label'=>false,'value'=>'Admin']);
				   			}
					
					?>
					</td>
				</tr>
				<tr>
					<td>
						<?php $options = array(
							    'label' => 'Delete',
							    'name' => 'Delete',
							);
						echo $this->Form->end($options); ?>
					</td>
					<td>
						<input type = 'button' value= 'Back' onclick = "location.href = 'index'" />
					</td>
				</tr>
			</table>
		<?php } ?>
</div>