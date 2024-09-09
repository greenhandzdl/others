#!/bin/bash
#: 描述：清理commit

###chmod -R +rw .git/objects


# 1. Backup current working directory
backup_dir="/tmp/git_backup_$(date +%Y%m%d%H%M%S)"
echo "Backing up current directory to $backup_dir ..."
mkdir -p $backup_dir
cp -a . $backup_dir

# 2. Perform git fetch to update remote branches
echo "Fetching latest changes from remote..."
git fetch --all

# 3. Hard reset local branch to match remote branch
echo "Resetting local branch to match remote branch..."
git reset --hard origin/master  # Replace 'master' with your branch name if needed

# 4. Rewrite commit history
echo "Rewriting commit history..."
# Note: This step is very sensitive and may affect your repository integrity.
# Create a new orphan branch with only the latest state
git checkout --orphan temp_branch

# Add all files and commit them
git add -A
git commit -m "Initial commit after history rewrite"

# Delete the old branch and rename the new one
git branch -D master  # Replace 'master' with your branch name if needed
git branch -m master  # Replace 'master' with your branch name if needed

# Force push the new branch to the remote repository
echo "Force pushing the new branch to remote repository..."
git push -f origin master  # Replace 'master' with your branch name if needed

# 5. Restore backed up files
echo "Restoring backed up files..."
cp -a $backup_dir/. .

# 6. Clean up temporary backup directory
echo "Cleaning up temporary backup directory..."
rm -rf $backup_dir

echo "Git history rewrite and optimization complete."