/* A handy function for doing pop-up confirmations when deleting something */
function deleteConfirmation(url)
{
	if (confirm("Are you really sure you want to delete this?\n\nOnce deleted it will be gone forever."))
	{
		document.location.href=url;
		return true;
	}
	else { return false; }
}

