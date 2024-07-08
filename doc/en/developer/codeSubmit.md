# How to submit my code to the repository
Once you finish your code, and pass all the tests. You needn't worry about code formatting,
`git action` will automatically format the code for you when you create a `pull request` to develop
branch or master branch. What you need to do is to make sure all your changes have been committed
locally, and make sure the commit messages are readable (meet the
[rules of commit messages](https://github.com/Kaiser-Yang/matrix-calculation-accelarator/assets/58209855/85d7c3e5-f83e-4f2f-b782-6f29e8ff0311)).

Now you can create a branch remotely, you can use `git push origin -u your-branch-name` to push your
branch to remote with the same name. After this, you can create a `pull request` to merge into
`develop` branch ( **choose the right branch**). Write the title and the description. The changes
will be checked by `git action`s. Once they passed, you just need to wait the collaborators to accept
your changes or give you some new suggestions.

# How to update when I was told
Sometime, your code may be add some reviews by the collaborators, you need update your code to
resolve these reviews.

You can update your local code to meet the collaborators' suggestions. After this, you can commit,
and then use `git push` to  update the remote branch (this will re-run `git action`s). These new
changes will be seen on the `pull request`, if you resolve the problem, you may click the `resolve`
for the review.

**Note: the below is not recommended.**

If you think the new commit can be submitted without creating a new commit, after you update your
code, you can use `git add` to add your code, then `git commit --amend` to let the new changes be
in the last commit. After this, you must use `git push -f` to update the remote forcedly.

# When to Merge Develop Branch into Master Branch
This will depend on me. Usually, when some new features are finished and tested, I'll create a
`release` branch to update version number and merge the `release` branch into `master` and
`develop`.

[Back to `How to build the project`](projectBuild.md)

[Back to the index](index.md)
