>*Partly refer to [a blog in CSDN]([Git教程 Git Bash详细教程-CSDN博客](https://blog.csdn.net/qq_36667170/article/details/79085301?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169926696716800185843905%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169926696716800185843905&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-79085301-null-null.142^v96^pc_search_result_base2&utm_term=git%20bash&spm=1018.2226.3001.4187))*
# Account setting

use fellow commands to set your accounts before doing anything else:

`git config --global user.name "userName"`

`git config --global user.email "emailAddress"`

Using `git config --list` to the the configs

# Local directories and files

1. create new files or directories:
	1. `mkdir dirName`: create a directory named dirName
	2. `touch fileName`: create a file named fileName
2. delete files or directories:
	1. `rm fileName`: delete the file fileName
	2. `rm -r dirName`: delete the directory dirName
3. enter and withdraw from specific directory:
	1. using command `cd` like: `cd d:/git/gitRepository/rep1`, or line by line like: `cd d` then `cd git` then `cd gitRepository` finally `cd rep1`
	2. `cd ..`: withdraw from the current directory
	3. `cd ~`: Enter your home directory
4. check the directories and files in recent directory
	1. `ls`: check what's in the current directory
	2. `ls -a`: list all the files and directories in the current directory, including the hidden
	3. `pwd`: check which directory you are currently in
5. Unzip files: `unzip file.zip`
6. Move files: `mv c:/users/username/filename d:/desktop/dirname`, move the file `filename` from `c:/users/username` to `d:/desktop/dirname`
7. Open the current directory: `start .`(on Windows)
8. The directory name with blank space should be enclosed by single quotes `''`
9. Rename files or directories: `git mv <oldFileName> <NewfileName>`(Only in git repositories)

# Repository

## 1. create a repository
First create a repository
1. initialize local repository: `git init`, this will create a .git directory in the current directory.
2. create remote repository: take github for example.
3. build the link between local and remote repositories.
	1. First configure SSH key in github, referring to [a guide for configuration of SSH key in Github](http://blog.csdn.net/qq_36667170/article/details/79094257)(But if you are not the master of the repository, you can only use HTTPS link)
	2. Second, open Git bash in local repository, and enter the fellow command: `git remote add repoName address`, `repoName` is the name of the remote repository(or you can create a new name, too), and `address` is the SSH address of the remote repository, which can be found in github, the format of which is `git@github.com:ownerName/repoName.git`
	3. Last, enter `git remote -v` to check whether you have done all these successfully

Then, if you want to fail the link with the remote repository, use `git remote remove repoName`

## 2. commands
Now, you may do some operations in your repository.
1. `git add`: upload the modified files into the ***staging area***
	1. `git add -A`: upload all changes of all files
	2. `git add fileName`: upload the change of a certain file
	3. `git add file1 file2 ... filen`: upload n files
	4. `git add dir/*.html`: upload all html files in the directory `dir`
	5. `git add *hhh`: upload all files ending with `hhh`
	6. `git add hello*`: upload all files beginning with `hello`
	7. `git add -u`: upload all modified or deleted files, excluding new files
	8. `git add .`: upload all new or modified files, excluding deleted files
2. `git commit`: upload the files in the staging area into the history of ***local repository***
	1. `git commit -m "good job"`: upload with a comment "good job"
3. `git push`: upload files to the ***remote repository***
	1. `git push -u repoName branchName`: upload the local repository to a ***empty*** remote repository, `repoName` is mentioned above, and `branchName` is the name of the branch you are pushing in, like `master` and `main`
	2. `git push repoName branchName`： upload the local repository to the remote repository, in other words the second or so time you push.
	3. `git push repoName branchName -f`: forced push(Sometimes, when you push your local repository, git may return an error to you, however, *avoid using it*)
4. `git log`: check your commit record
5. `git status`: check the status of each file incurrent repository.
6. `git show <ID>`: show the contents of the commit with certain ID(The ID can be seen by  `git log`)
![[Git的结构示意图.png]]
![](https://sp18.datastructur.es/materials/guides/img/file-status.png)
There may be some mistakes in your commit. Anyway you can use the fellow commands to amend them.
1. `git commit --amend -m "sjtu"`: amend the original **comment** to `sjtu`
2. Amend the **file name**: First amend the file name on your computer, then use`git add -A`-> (`git commit -m "Amending the file name of ...")`->`git push repoName branchName`
3. Undo some commits: use `git reset HEAD [file]` to make some or all the files' status back to modified
4. Revert a file to its state in the most recent commit: `git checkout -- [file]`

After some commits, you may want to rearrange the repository in some older versions. Do:`git checkout <ID> <file>` to realize that. If you didn't specify a file or a directory, the command will rearrange the whole repository!!!

## 3. pull from the remote

When you work in a team, there are occasions where your teammates changed the remote repository, if you want to push your local repository to the remote, there would be an error, for the local repository before you commit and the remote repository are not the same(The same reason for the above changing of comments). You can try the following methods.
1. `git pull repoName`: get the remote repository to merge your local repository.
2. `git fetch` +`git merge`: The first command get the remote repository, and the second command let it merge with the local repository. We can take it that `pull` equals to `fetch` + `merge`

## 4. review
Now let's stop our foot to learn something more about git and review what we do to `push` and `pull`:
1. `push`:
	1. First we use command `git add` to *add changes to the staging area*.
	2. Then we use command `git commit` to *upload changes in the staging area to (the history of) local repository*.
	3. Finally we use command `git push` to *change the remote repository*.
2. `pull`:
	1. We could use command `git pull` by one step.
	2. Or we can also use commands `git fetch` and `git merge` to do the same thing.

## 5. clone

Now we are going to learn how to clone a repository.

First come to the directory where you are going to clone the remote repository, and open git bash here.

Then use command `git clone address`, `address` has been mentioned above, which is the location of the remote repository in github, having a format such as `git@github.com:ownerName/repoName.git`.

There are some differences of `pull` and `clone`:
1. `git pull`: must be linked with the remote repository if to be used. Download complete codes and update the local codes.
2. `git clone`: only for downloading the codes in remote repository, doesn't need to be linked with the remote, doesn't apply to update the local codes. 

# Branches

>*Very important!!!*

1. Set your default branch name: `git config --global init.defaultBranch <name>`
2. Change the current branch name: `git branch -m <new-name>`