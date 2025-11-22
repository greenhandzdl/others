#!/bin/bash
git branch -v | awk '{ if ($1 == "*") print $2; else print $1 }' | while read branch; do
    echo "Updating branch: $branch"
    git checkout "$branch"
    git pull upstream "$branch" || echo "Failed to pull $branch"
    git push --set-upstream origin "$branch" || echo "Failed to push $branch"
done
