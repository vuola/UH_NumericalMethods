#!/bin/sh

INPUT="${1:-README.md}"
OUTPUT="${2:-index.html}"

if [ ! -f "$INPUT" ]; then
  echo "Error: input file '$INPUT' not found." >&2
  exit 1
fi

cat > "$OUTPUT" <<'EOF'
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Submission Index</title>
  <style>
    body {
      font-family: system-ui, -apple-system, sans-serif;
      margin: 2em;
      max-width: 1100px;
    }
    h1, h2, h3 {
      margin-top: 1.5em;
    }
    ul {
      margin-left: 1.5em;
    }
    li {
      margin: 0.2em 0;
    }
    code {
      background: #f5f5f5;
      padding: 0.1em 0.3em;
      border-radius: 3px;
    }
    a {
      color: #0645ad;
      text-decoration: none;
    }
    a:hover {
      text-decoration: underline;
    }
    blockquote {
      border-left: 4px solid #ccc;
      padding-left: 1em;
      color: #555;
    }
  </style>
</head>
<body>
EOF

awk '
function escape_html(s) {
  gsub(/&/, "\\&amp;", s)
  gsub(/</, "\\&lt;", s)
  gsub(/>/, "\\&gt;", s)
  return s
}

function rewrite_path(url) {
  if (url ~ /^exercise[0-9]+\/.*\.py$/) {
    sub(/^exercise/, "scripts/exercise", url)
  } else if (url ~ /^exercise[0-9]+\//) {
    sub(/^exercise/, "answers/exercise", url)
  }
  return url
}

# Standalone shell command in backticks → preformatted block
/^[[:space:]]*`[^`]+`[[:space:]]*$/ {
  close_ul()
  line = $0
  sub(/^[[:space:]]*`/, "", line)
  sub(/`[[:space:]]*$/, "", line)
  print "<pre><code>" escape_html(line) "</code></pre>"
  next
}

function convert_links(s,   pre, link, post, text, url) {
  while (match(s, /\[[^]]+\]\([^)]+\)/)) {
    pre  = substr(s,1,RSTART-1)
    link = substr(s,RSTART,RLENGTH)
    post = substr(s,RSTART+RLENGTH)

    text = link
    sub(/^\[/,"",text)
    sub(/\]\(.*/,"",text)

    url = link
    sub(/.*\]\(/,"",url)
    sub(/\)$/,"",url)

    url = rewrite_path(url)

    s = pre "<a href=\"" url "\">" escape_html(text) "</a>" post
  }
  return s
}

function close_ul() {
  if (in_ul) {
    print "</ul>"
    in_ul = 0
  }
}

BEGIN { in_ul = 0 }

/^### / {
  close_ul()
  print "<h3>" escape_html(substr($0,5)) "</h3>"
  next
}

/^## / {
  close_ul()
  print "<h2>" escape_html(substr($0,4)) "</h2>"
  next
}

/^# / {
  close_ul()
  print "<h1>" escape_html(substr($0,3)) "</h1>"
  next
}

/^[[:space:]]*- / {
  if (!in_ul) {
    print "<ul>"
    in_ul = 1
  }
  line = $0
  sub(/^[[:space:]]*- /, "", line)
  line = convert_links(line)
  print "<li>" line "</li>"
  next
}

/^$/ {
  close_ul()
  next
}

{
  close_ul()
  if ($0 ~ /^>/) {
    line = substr($0,2)
    sub(/^ /,"",line)
    line = convert_links(line)
    print "<blockquote>" line "</blockquote>"
  } else {
    line = convert_links($0)
    print "<p>" escape_html(line) "</p>"
  }
}

END { close_ul() }
' "$INPUT" >> "$OUTPUT"


cat >> "$OUTPUT" <<'EOF'
</body>
</html>
EOF

echo "Created $OUTPUT successfully."
