lista de posibilidades corregidas con el $

$				--> $: command not found
$$				--> \n
$$$				--> $: command not found
$ $ $			--> $: command not found
$ls				--> \n
ls$				--> ls$: command not found
$$ls$$ $$-a		--> ls -a Normal
ls$$$-a			--> ls Normal
ls$a			--> ls Normal
