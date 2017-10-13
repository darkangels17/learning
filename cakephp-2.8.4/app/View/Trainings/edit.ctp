<div>
	<lable>管理システム</label>
	<?php echo $this->Form->create('Training'); ?>
		<?php if(isset($error)) { ?>
		<div class = 'err'>
			<?=$error ?>
		</div>
		<?php } ?>
		<?php if(isset($user)) {?>
			<table>
				<tr>
					<td> User Name </td>
					<td><?php echo $this->Form->input('userName',['label'=>false,'value'=>$user['Training']['userName']]);?></td>
				</tr>
				<tr>
					<td> Email </td>
					<td><?php echo $this->Form->input('emailEdit',['label'=>false,'value'=>$user['Training']['email']]);?></td>
				</tr>
				<tr>
					<td> Address </td>
					<td><?php echo $this->Form->input('address',['label'=>false,'value'=>$user['Training']['userName']]);?></td>
				</tr>
				<tr>
					<td> Birthday </td>
					<td><?php echo $this->Form->input('birthday',['type'=>'text','label'=>false,'value'=>$user['Training']['birthday']]);?></td>
				</tr>
				<tr>
					<td> Member Type </td>
					<td><?php echo $this->Form->input('type',['label'=> false, 'type' => 'select','multiple' => false ,'options'=>['User','Admin'],'selected' => $user['Training']['type']]);?></td>
				</tr>
			</table>
		<?php } ?>
	<center><?php  echo $this->Form->end('Update',['name'=>'Update']);?></center>
</div>