Development on GitHub 
=====================
SciPy development largely takes place on GitHub; this section describes the
expected way of working for issues, pull requests and managing the main
``scipy`` repository.

.. _labels-and-milestones:

Labels and Milestones
---------------------
Each issue and pull request normally gets at least two labels: one for the
topic or component (``scipy.stats``, ``Documentation``, etc.), and one for the
nature of the issue or pull request (``enhancement``, ``maintenance``,
``defect``, etc.).  Other labels that may be added depending on the situation:

- ``easy-fix``: for issues suitable to be tackled by new contributors.
- ``needs-work``: for pull requests that have review comments that haven't been
  addressed.
- ``needs-decision``: for issues or pull requests that need a decision.
- ``needs-champion``: for pull requests that were not finished by the original
  author, but are worth resurrecting.
- ``backport-candidate``: bugfixes that should be considered for backporting by
  the release manager.

A milestone is created for each version number for which a release is planned.
Issues that need to be addressed and pull requests that need to be merged for a
particular release should be set to the corresponding milestone.  After a pull
request is merged, its milestone (and that of the issue it closes) should be
set to the next upcoming release - this makes it easy to get an overview of
changes and to add a complete list of those to the release notes.


Pull request review workflow
----------------------------

When reviewing pull requests, please make use of pull request workflow tracking
features on GitHub as appropriate:

1. After you have finished reviewing, and want to ask for the submitter
   to make the changes:

   - Change your review status to "Changes requested".

     This can be done on Github, PR page, ``Files changed`` tab,
     ``Review changes`` (button on top right).

   - Alternatively: add the ``needs-work`` label.

     This can be done on the PR page, ``Labels`` menu on the right.

2. When you re-review the same pull request again, and want to request
   more changes:

   - Do the "Changes requested" thing again, even if the previous status
     was also 'Changes requested'.

   - Alternatively:
     Remove the existing ``needs-work`` label, and then re-add the label
     back again. (Github will add a notice on the page that you did so.)

3. If you're happy about the current status:

   - Mark the pull request as Approved (same way as Changes requested).

   - Alternatively: remove the ``needs-work`` label.

   - Alternatively (for core developers): merge the pull request, if
     you think it is ready to be merged.

This allows automatically tracking which PRs are in need of attention.

The review status is listed at: https://pav.iki.fi/scipy-needs-work/
The page can also be generated using https://github.com/pv/github-needs-work

Some of the information is also visible on Github directly, although
(as of Aug 2019) Github does not show which pull requests have been
updated since the last review.


Code from pull request
----------------------

When you review a pull request created by someone else, it's helpful to have a
copy of their code on your own machine so that you can play with it locally.

One way to do this is to navigate to the SciPy root directory in the terminal
and enter::

   git fetch upstream pull/PULL_REQUEST_ID/head:NEW_BRANCH_NAME

where ``PULL_REQUEST_ID`` is the five digit number corresponding with the
pull request (e.g. ``10286`` for `PR #10286`_) and ``NEW_BRANCH_NAME`` is
whatever name you'd like to use to refer to the author's code (e.g.
``review_10286``).

Now you can check out the branch::

   git checkout NEW_BRANCH_NAME

which converts the code in your local repository to match the author's modified
version of SciPy.

Assuming you set up your development environment according to one of the
:ref:`dev-env` pages, you can now activate your development environment::

   conda activate scipy-dev

build the code and test it::

   python dev.py test -v

and if you ``import`` SciPy from Python, you'll be importing the
author's modified version of SciPy.

If you want to collaborate with the author on their PR, you might instead
want to set up a new remote to the author's fork of SciPy::

   git remote add REMOTE_NAME https://github.com/AUTHOR/scipy.git

where ``AUTHOR`` is the author's GitHub user name and ``REMOTE_NAME`` is
whatever name you want to use to refer to this author's repository.

From there, you can view the author's branches::

   git remote show REMOTE_NAME

and create your own branch based on one of them::

   git checkout --track REMOTE_NAME/BRANCH_NAME

where ``BRANCH_NAME`` is the name of the branch you want to start from. This
creates a copy of this branch (with the same name) in your local repository.
If make changes to this branch and push to your GitHub repository
(``origin``), you can then create a pull request to merge your changes with the
author's repository.

.. _PR #10286: https://github.com/scipy/scipy/pull/10286



Dealing with pull requests
--------------------------

- When merging contributions, a committer is responsible for ensuring that
  those meet the requirements outlined in `Contributing to SciPy
  <https://github.com/scipy/scipy/blob/main/HACKING.rst.txt>`_. Also check
  that new features and backwards compatibility breaks were discussed on the
  scipy-dev mailing list.
- New code goes in via a pull request (PR).
- Merge new code with the green button.  In case of merge conflicts, ask the PR
  submitter to rebase (this may require providing some git instructions).
- Backports and trivial additions to finish a PR (really trivial, like a typo
  or PEP8 fix) can be pushed directly.
- For PRs that add new features or are in some way complex, wait at least a day
  or two before merging it.  That way, others get a chance to comment before
  the code goes in.
- Squashing commits or cleaning up commit messages of a PR that you consider
  too messy is OK. Make sure though to retain the original author name when
  doing this.
- Make sure that the labels and milestone on a merged PR are set correctly.
- When you want to reject a PR: if it's very obvious you can just close it and
  explain why, if not obvious then it's a good idea to first explain why you
  think the PR is not suitable for inclusion in SciPy and then let a second
  committer comment or close.


.. _backporting:

Backporting
-----------
All pull requests (whether they contain enhancements, bug fixes or something else),
should be made against main.  Only bug fixes are candidates for backporting
to a maintenance branch.  The backport strategy for SciPy is to (a) only backport
fixes that are important, and (b) to only backport when it's reasonably sure
that a new bugfix release on the relevant maintenance branch will be made.
Typically, the developer who merges an important bugfix adds the
``backport-candidate`` label and pings the release manager, who decides on
whether and when the backport is done.  After the backport is completed, the
``backport-candidate`` label has to be removed again.

A good strategy for a backport pull request is to combine several main
branch pull requests, to reduce the burden on continuous integration tests
and to reduce the merge commit cluttering of maintenance branch history. It
is generally best to have a single commit for each of the main branch pull
requests represented in the backport pull request. This way, history is clear
and can be reverted in a straightforward manner if needed.

Release notes
-------------
When a PR gets merged, consider if the changes need to be mentioned in the
release notes.  What needs mentioning: new features, backwards incompatible
changes, deprecations, and "other changes" (anything else noteworthy enough,
see older release notes for the kinds of things worth mentioning).

Release note entries are maintained on the wiki, (e.g.
https://github.com/scipy/scipy/wiki/Release-note-entries-for-SciPy-1.2.0).  The
release manager will gather content from there and integrate it into the html
docs.  We use this mechanism to avoid merge conflicts that would happen if
every PR touched the same file under ``doc/release/`` directly.

Changes can be monitored (`Atom feed <https://github.com/scipy/scipy/wiki.atom>`_)
and pulled (the wiki is a git repo: ``https://github.com/scipy/scipy.wiki.git``).


Other
-----
*PR status page:* When new commits get added to a pull request, GitHub doesn't send out any
notifications.  The ``needs-work`` label may not be justified anymore though.
`This page <https://pav.iki.fi/scipy-needs-work/>`_ gives an overview of PRs
that were updated, need review, need a decision, etc.

*Cross-referencing:* Cross-referencing issues and pull requests on GitHub is
often useful.  GitHub allows doing that by using ``gh-xxxx`` or ``#xxxx`` with
``xxxx`` the issue/PR number.  The ``gh-xxxx`` format is strongly preferred,
because it's clear that that is a GitHub link.  Older issues contain ``#xxxx``
which is about Trac (what we used pre-GitHub) tickets.

*PR naming convention:* Pull requests, issues and commit messages usually start
with a three-letter abbreviation like ``ENH:`` or ``BUG:``.  This is useful to
quickly see what the nature of the commit/PR/issue is.  For the full list of
abbreviations, see :ref:`writing the commit message
<numpy:writing-the-commit-message>`.
