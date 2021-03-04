all: 
	bundle exec jekyll serve
	
merge: 
	git remote update && git merge dt-np/master 

 
