
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

<label><b>Total User</b>: 7 </label> 
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
		<td><?=$user['Training']['UserId']?></td>
		<td><?=$user['Training']['UserName']?></td>
		<td><?=$user['Training']['Email']?></td>
		<td><?=$user['Training']['Birthday']?></td>
		<td><?=$user['Training']['Address']?></td>
		<td><?=$user['Training']['Type']?></td>
		<td><a href = "#" >Edit</a>| <a href="#">Delete</a></td>
	</tr>
<?php }?>
</table>
 