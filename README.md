[![codecov](https://codecov.io/gh/Kaiser-Yang/matrix-calculation-accelerator/graph/badge.svg?token=INWEC8613W)](https://codecov.io/gh/Kaiser-Yang/matrix-calculation-accelerator)

# matrix-calculation-accelerator

## Brief Introduction
Matrix calculation implemented by C++ with multi-thread.  This will implement some basic calculations of matrices, such `+`, `-`, `*`, `/`, etc.

## What Can You Learn From This
Those below are what you can learn:
* The basic usages of `git`
* How to write a reasonable and readable commit message
* The whole `gitflow` process
* The basic usage of `cmake`
* The `CI` process
* How to write unit tests with `GoogleTest`
* How to generate code coverage report with `lcov`
* ...

# Release Log
`v0.1.2`:
* This version adds titles of the statistical figures.

`v0.1.1`:
* This version updates the `url` of `codecov`.

`v0.1.0`:
* This version has finished all the needed methods by multi-thread calculation.

`v0.0.3`:
* This version substitutes `multi thread` with `multi-thread`.

`v0.0.2`:
* This version substitutes the `#` with `*`.

`v0.0.1`:
* This version adds a git flow for clang format check.

`v0.0.0`:
* This is the initial commit. We finish `cmake` configure, `googletest` configure, and add `github workflow`.

# Statistics
Composition of code lines:

![image](https://github.com/Kaiser-Yang/matrix-calculation-accelerator/assets/58209855/7c18251a-2f2c-4618-ac30-fe06462b20c7)

Composition of commits per person:

![image](https://github.com/Kaiser-Yang/matrix-calculation-accelerator/assets/58209855/d067eed2-b5c3-475c-b656-eaeab62a2db6)

Test code and project code's composition:

![image](https://github.com/Kaiser-Yang/matrix-calculation-accelerator/assets/58209855/a62b6cb7-9b7f-43f4-925d-459abca0a009)

Git branch graph:

![image](https://github.com/Kaiser-Yang/matrix-calculation-accelerator/assets/58209855/bd48df2b-351b-414b-bd71-81be0dbf7b27)

# Learning Materials
If you don't know how to use `git`, you can read this: [Version Control (git)](https://missing.csail.mit.edu/2020/version-control/), [Learn Git](https://learngitbranching.js.org/?locale=zh_CN)

If you don't know `git flow`, you can read these to learn git flow: [My own understanding of Gitflow](https://blog.csdn.net/qq_45523675/article/details/138200604), [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model)

If you don't know how to write tests through `GoogleTest`, you can read this: [GoogleTest Primer](https://google.github.io/googletest/primer.html)

If you don't know how to write commit messages, you can look at this: [How to write commit messages](https://cbea.ms/git-commit/)

Here is a screenshot for rules of writing commit messages:
![2b6482d61a8808e8d37757e283d3aa6](https://github.com/Kaiser-Yang/matrix-calculation-accelarator/assets/58209855/85d7c3e5-f83e-4f2f-b782-6f29e8ff0311)

# How to Write My Own Codes?
Once you clone the repository, you should make sure that you are on the `develop` branch, you can use `git checkout develop` to convert to `develop` branch. After this, you'd better run `git pull` to make sure the `develop` branch is up to date.

Usually, you cannot commit on `develop` and `master` branches (You can commit locally, but you cannot push, and you can only make updates on these branches through `pull request`). So if you want your codes be submitted to the repository, you can create a new branch depending on `develop` ( through `git checkout -b new-branch-name develop`) and write your own codes on the new branch.

# How to Build the Project?
**If you are familiar with `CMake` and `GoogleTest`, you can skip this part.**

Once you finish your codes on your new branch, you may need to compile the codes to make sure the codes can be compiled. Let me introduce you how to compile the project:
1. Make sure you are in the root directory of the repository.
2. Run `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -Dmca_BUILD_TEST=on -Dmca_GENERATE_COVERAGE=off`. `CMAKE_BUILD_TYPE` is to control the building version. `mca_BUILD_TESTS` is to control whether or not to build unit tests. `mca_GENERATE_COVERAGE` is to control whether or not to generate code coverage reports. Mostly, you needn't update those variables.
3. Run `cd build && cmake --build . -j64`, you can update `64` with any other positive number to specify how many threads you want to use when building the project (You'd better make sure it not exceed the number of your `cpu` cores or `cpu` super-threads). If there is no any error, CONGRATULATIONS, your codes can be compiled successfully.

If you want the build process same with `git actions`, you need make sure `clang-tidy` is available on your computer. If you use `UNIX-like` system, you can use `sudo apt-get install clang-tidy` to install `clang-tidy`. If you don't install `clang-tidy` the codes you write may be compiled successfully locally, but may not pass the `git actions`.

Although you compile your codes successfully, you should be aware of that the codes which is compiled successfully may not work properly. So you need write unit tests for the every function you write. So you need create a file which is related with your new codes. The filename usually is the origin base filename followed by `_test.cpp`. If there have been already one, you just need append your unit tests codes. If you finish writing unit tests, you can re-build the project through step `1-3` above. And change you directory to `build/test` (after building successfully), then run `ctest --output-on-failure`, this will start run all the test units. If all the tests pass, CONGRATULATIONS, your codes may be OK. If there are some tests failed, you need check the codes you write (both test codes and the source codes), and update them to pass all the tests.

# How to Submit My Codes to the Repository.
Once you finish your codes, and pass all the tests. You must run `clang-format -i src/*.cpp src/include/mca/*.h test/src/*.cpp src/include/mca/__mca_internal/*.h example/*.cpp example/include/*.h` to format your codes automatically (make sure you are in the root directory of the repository). Then make sure all you changed have been committed locally, and make sure the commit messages are readable (meet the rules).

Now you can create a branch remotely, you can use `git push origin -u your-branch-name` to push your branch to remote with the same name. After this, you can create a `pull request` to merge into `develop` branch ( **choose the right branch**). Write the title and the description. The changes will be checked by `git actions`. Once it passed, you can copy the `url` and send it to another collaborator to let him/her check you codes. Once the collaborator checked the changes, your codes will be in `develop` branch, you can update your local `develop` after this (`git checkout develop; git pull`).

If you have merged the remote branch into `develop`, and you are sure your branch will not be used, you are supposed to delete the remote branch created by you. You can use `git push origin -d remote-branch-name` to delete a remote branch.

# How to Update When I was Told?
Sometime, your codes may be add some reviews by the collaborators, you need update your codes to resolve these reviews.

You can update your local codes to meet the collaborators' suggestions. After this, you can commit, and then use `git push` to  update the remote branch (this will re-run `git actions`). These new changes will be seen on the `pull request`, if you resolve the problem, you may click the `resolve` for the review. 

**Note: the below is not recommended.**

If you think the new commit can be submitted without creating a new commit, after you update your codes, you can use `git add` to add your codes, then `git commit --amend` to let the new changes be in the last commit. After this, you must use `git push -f` to update the remote forcedly.

# When to Merge Develop Branch into Master Branch
This will depend on me.  Usually, when some new features finished and tested, I'll create a `release` branch to update version number and merge the `release` branch into `master` and `develop`.
