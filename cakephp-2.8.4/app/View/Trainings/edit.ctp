<div>
	<lable><a href = "#">管理システム</a></label>
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
					<td><?php echo $this->Form->input('email',['readonly'=> $readOnly,'label'=>false,'value'=>$user['Training']['email']]);?></td>
				</tr>
				<tr>
					<td> Address </td>
					<td><?php echo $this->Form->input('address',['readonly'=> $readOnly,'label'=>false,'value'=>$user['Training']['address']]);?></td>
				</tr>
				<tr>
					<td> Birthday </td>
					<td><?php echo $this->Form->input('birthday',['readonly'=> $readOnly,'type'=>'text','label'=>false,'value'=>$user['Training']['birthday']]);?></td>
				</tr>
				<tr>
					<td> Member Type </td>
					<td><?php
 						echo $this->Form->input('type', [
 							'options' => ['0'=>'User','1'=>'Admin'],
 							'default' => $user['Training']['type'],
 							'type' =>'radio',
 							]);
						?>
					</td>
				</tr>
				<tr>
					<td> 
						<?php if(!$readOnly) {echo $this->Form->end(['label'=>'Update','name'=>'Update']);} ?> 
					</td>
					<td>
						<input type = 'button' value= 'Back' onclick = "location.href = 'index'" />
					</td>
				</tr>
			</table>
		<?php } ?>
		

	
</div>