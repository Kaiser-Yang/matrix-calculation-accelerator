# How to write my own code
Once you clone the repository, you should make sure that you are on the `develop` branch, you can
use `git checkout develop` to convert to `develop` branch. After this, you'd better run `git pull`
to make sure the `develop` branch is up to date.

Usually, you cannot commit on `develop` and `master` branches (You can commit locally, but you
cannot push, and you can only make updates on these branches through `pull request`). So if you
want your code to be submitted to the repository, you can create a new branch depending on `develop`
(through `git checkout -b new-branch-name develop`) and write your own code on the new branch. Of
course, if you are not one of the developers of the repository, you need folk this repository, and
update on your own repository, then create a pull request depending on the folked repository.


[Next: `How to build the project`](projectBuild.md)

[Back to the index](index.md)

